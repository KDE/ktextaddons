/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserverstreamablehttptest.h"
#include "streamablehttp/mcpclientstreamablehttpplugininterface.h"
#include "streamablehttp/mcpserverstreamhttpplugininterface.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSignalSpy>
#include <QTcpServer>
#include <QTest>
#include <memory>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpServerStreamableHttpTest)

namespace
{
QJsonObject jsonRequest(const QString &method, const QJsonValue &id)
{
    return QJsonObject{{"jsonrpc"_L1, u"2.0"_s}, {"id"_L1, id}, {"method"_L1, method}};
}

QJsonObject jsonNotification(const QString &method)
{
    return QJsonObject{{"jsonrpc"_L1, u"2.0"_s}, {"method"_L1, method}};
}

QJsonObject result(const QJsonValue &id, const QJsonObject &result = {})
{
    return QJsonObject{{"jsonrpc"_L1, u"2.0"_s}, {"id"_L1, id}, {"result"_L1, result}};
}

QJsonObject initializeResult(const QJsonValue &id)
{
    return result(id,
                  QJsonObject{{"protocolVersion"_L1, u"2025-11-25"_s},
                              {"capabilities"_L1, QJsonObject{}},
                              {"serverInfo"_L1, QJsonObject{{"name"_L1, u"server"_s}, {"version"_L1, u"1"_s}}}});
}

QUrl freeUrl()
{
    QTcpServer server;
    server.listen(QHostAddress::LocalHost);
    return QUrl(u"http://127.0.0.1:%1/mcp"_s.arg(server.serverPort()));
}

// Server which answers each request with an empty result
std::unique_ptr<McpServerStreamHttpPluginInterface> createServer(const QUrl &url, const QByteArray &authToken = {})
{
    auto server = std::make_unique<McpServerStreamHttpPluginInterface>();
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setServerUrl(url);
    settings.setAuthToken(authToken);
    server->setSettings(settings);
    McpServerStreamHttpPluginInterface *serverPtr = server.get();
    QObject::connect(serverPtr, &McpServerStreamHttpPluginInterface::received, serverPtr, [serverPtr](const QJsonObject &obj) {
        if (!obj.contains("id"_L1)) {
            return;
        }
        if (obj.value("method"_L1).toString() == "initialize"_L1) {
            serverPtr->send(initializeResult(obj.value("id"_L1)));
        } else {
            serverPtr->send(result(obj.value("id"_L1)));
        }
    });
    QSignalSpy startedSpy(serverPtr, &McpServerStreamHttpPluginInterface::started);
    server->start();
    if (startedSpy.count() != 1) {
        return {};
    }
    return server;
}

QNetworkReply *
post(QNetworkAccessManager &manager, const QUrl &url, const QByteArray &body, const QByteArray &sessionId = {}, const QByteArray &authorization = {})
{
    QNetworkRequest request(url);
    request.setRawHeader("Accept"_ba, "application/json, text/event-stream"_ba);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json"_ba);
    if (!sessionId.isEmpty()) {
        request.setRawHeader("Mcp-Session-Id"_ba, sessionId);
    }
    if (!authorization.isEmpty()) {
        request.setRawHeader("Authorization"_ba, authorization);
    }
    return manager.post(request, body);
}

QByteArray toJson(const QJsonObject &obj)
{
    return QJsonDocument(obj).toJson(QJsonDocument::Compact);
}

int statusCode(QNetworkReply *reply)
{
    return reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
}

// Initialize a session and return its id
QByteArray initializeSession(QNetworkAccessManager &manager, const QUrl &url, const QByteArray &authorization = {})
{
    std::unique_ptr<QNetworkReply> reply(post(manager, url, toJson(jsonRequest(u"initialize"_s, 1)), {}, authorization));
    QSignalSpy finishedSpy(reply.get(), &QNetworkReply::finished);
    if (!finishedSpy.wait()) {
        return {};
    }
    return reply->rawHeader("Mcp-Session-Id"_ba);
}
}

McpServerStreamableHttpTest::McpServerStreamableHttpTest(QObject *parent)
    : QObject{parent}
{
}

void McpServerStreamableHttpTest::shouldNotStartWithInvalidUrl()
{
    McpServerStreamHttpPluginInterface server;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    // No port
    settings.setServerUrl(QUrl(u"http://127.0.0.1/mcp"_s));
    server.setSettings(settings);
    QSignalSpy startedSpy(&server, &McpServerStreamHttpPluginInterface::started);
    QSignalSpy errorSpy(&server, &McpServerStreamHttpPluginInterface::error);
    QSignalSpy finishedSpy(&server, &McpServerStreamHttpPluginInterface::finished);
    server.start();
    QCOMPARE(startedSpy.count(), 0);
    QCOMPARE(errorSpy.count(), 1);
    QCOMPARE(finishedSpy.count(), 1);
}

void McpServerStreamableHttpTest::shouldExchangeMessagesWithClient()
{
    const QUrl url = freeUrl();
    auto server = createServer(url);
    QVERIFY(server);
    QSignalSpy serverReceivedSpy(server.get(), &McpServerStreamHttpPluginInterface::received);

    McpClientStreamableHttpPluginInterface client;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setServerUrl(url);
    client.setSettings(settings);
    QSignalSpy clientReceivedSpy(&client, &McpClientStreamableHttpPluginInterface::received);
    QSignalSpy clientErrorSpy(&client, &McpClientStreamableHttpPluginInterface::error);
    client.start();

    // Initialize: answer in POST response
    client.send(jsonRequest(u"initialize"_s, 1));
    QTRY_COMPARE(clientReceivedSpy.count(), 1);
    QCOMPARE(clientReceivedSpy.at(0).at(0).toJsonObject(), initializeResult(1));
    QCOMPARE(serverReceivedSpy.at(0).at(0).toJsonObject(), jsonRequest(u"initialize"_s, 1));

    // Notification: 202 without body
    client.send(jsonNotification(u"notifications/initialized"_s));
    QTRY_COMPARE(serverReceivedSpy.count(), 2);
    QCOMPARE(serverReceivedSpy.at(1).at(0).toJsonObject(), jsonNotification(u"notifications/initialized"_s));

    // Request with session
    client.send(jsonRequest(u"tools/list"_s, u"abc"_s));
    QTRY_COMPARE(clientReceivedSpy.count(), 2);
    QCOMPARE(clientReceivedSpy.at(1).at(0).toJsonObject(), result(u"abc"_s));

    // Messages sent by server use event stream opened by client
    server->send(jsonNotification(u"notifications/tools/list_changed"_s));
    QTRY_COMPARE(clientReceivedSpy.count(), 3);
    QCOMPARE(clientReceivedSpy.at(2).at(0).toJsonObject(), jsonNotification(u"notifications/tools/list_changed"_s));
    QCOMPARE(clientErrorSpy.count(), 0);
}

void McpServerStreamableHttpTest::shouldRejectRequestWithoutSession()
{
    const QUrl url = freeUrl();
    auto server = createServer(url);
    QVERIFY(server);
    QSignalSpy serverReceivedSpy(server.get(), &McpServerStreamHttpPluginInterface::received);
    QNetworkAccessManager manager;

    // Not initialized
    std::unique_ptr<QNetworkReply> reply(post(manager, url, toJson(jsonRequest(u"tools/list"_s, 1))));
    QSignalSpy finishedSpy(reply.get(), &QNetworkReply::finished);
    QVERIFY(finishedSpy.wait());
    QCOMPARE(statusCode(reply.get()), 400);

    // Initialized but no session header
    QVERIFY(!initializeSession(manager, url).isEmpty());
    reply.reset(post(manager, url, toJson(jsonRequest(u"tools/list"_s, 2))));
    QSignalSpy finishedSpy2(reply.get(), &QNetworkReply::finished);
    QVERIFY(finishedSpy2.wait());
    QCOMPARE(statusCode(reply.get()), 400);
    // Only initialize request was received
    QCOMPARE(serverReceivedSpy.count(), 1);
}

void McpServerStreamableHttpTest::shouldRejectRequestWithUnknownSession()
{
    const QUrl url = freeUrl();
    auto server = createServer(url);
    QVERIFY(server);
    QNetworkAccessManager manager;
    QVERIFY(!initializeSession(manager, url).isEmpty());
    std::unique_ptr<QNetworkReply> reply(post(manager, url, toJson(jsonRequest(u"tools/list"_s, 2)), "unknown"_ba));
    QSignalSpy finishedSpy(reply.get(), &QNetworkReply::finished);
    QVERIFY(finishedSpy.wait());
    QCOMPARE(statusCode(reply.get()), 404);
}

void McpServerStreamableHttpTest::shouldRejectInvalidRequests()
{
    const QUrl url = freeUrl();
    auto server = createServer(url);
    QVERIFY(server);
    QNetworkAccessManager manager;
    const QByteArray sessionId = initializeSession(manager, url);
    QVERIFY(!sessionId.isEmpty());

    const auto check = [&manager](QNetworkReply *networkReply, int expectedStatus) {
        std::unique_ptr<QNetworkReply> reply(networkReply);
        QSignalSpy finishedSpy(reply.get(), &QNetworkReply::finished);
        QVERIFY(finishedSpy.wait());
        QCOMPARE(statusCode(reply.get()), expectedStatus);
    };
    // Invalid json
    check(post(manager, url, "{"_ba, sessionId), 400);
    // Wrong path
    QUrl otherUrl = url;
    otherUrl.setPath(u"/other"_s);
    check(post(manager, otherUrl, toJson(jsonRequest(u"tools/list"_s, 2)), sessionId), 404);
    // Origin of a remote web page
    QNetworkRequest originRequest(url);
    originRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json"_ba);
    originRequest.setRawHeader("Mcp-Session-Id"_ba, sessionId);
    originRequest.setRawHeader("Origin"_ba, "http://evil.example.com"_ba);
    check(manager.post(originRequest, toJson(jsonRequest(u"tools/list"_s, 3))), 403);
    // Event stream must be accepted by client
    QNetworkRequest getRequest(url);
    getRequest.setRawHeader("Accept"_ba, "application/json"_ba);
    getRequest.setRawHeader("Mcp-Session-Id"_ba, sessionId);
    check(manager.get(getRequest), 406);
    // Unsupported method
    QNetworkRequest putRequest(url);
    putRequest.setRawHeader("Mcp-Session-Id"_ba, sessionId);
    check(manager.put(putRequest, QByteArray()), 405);
}

void McpServerStreamableHttpTest::shouldAnswerBatch()
{
    const QUrl url = freeUrl();
    auto server = createServer(url);
    QVERIFY(server);
    QNetworkAccessManager manager;
    const QByteArray sessionId = initializeSession(manager, url);
    QVERIFY(!sessionId.isEmpty());

    const QJsonArray batch{jsonRequest(u"tools/list"_s, 2), jsonNotification(u"notifications/progress"_s), jsonRequest(u"prompts/list"_s, 3)};
    std::unique_ptr<QNetworkReply> reply(post(manager, url, QJsonDocument(batch).toJson(QJsonDocument::Compact), sessionId));
    QSignalSpy finishedSpy(reply.get(), &QNetworkReply::finished);
    QVERIFY(finishedSpy.wait());
    QCOMPARE(statusCode(reply.get()), 200);
    QCOMPARE(QJsonDocument::fromJson(reply->readAll()).array(), QJsonArray({result(2), result(3)}));
}

void McpServerStreamableHttpTest::shouldTerminateSession()
{
    const QUrl url = freeUrl();
    auto server = createServer(url);
    QVERIFY(server);
    QNetworkAccessManager manager;
    const QByteArray sessionId = initializeSession(manager, url);
    QVERIFY(!sessionId.isEmpty());

    QNetworkRequest deleteRequest(url);
    deleteRequest.setRawHeader("Mcp-Session-Id"_ba, sessionId);
    std::unique_ptr<QNetworkReply> reply(manager.deleteResource(deleteRequest));
    QSignalSpy finishedSpy(reply.get(), &QNetworkReply::finished);
    QVERIFY(finishedSpy.wait());
    QCOMPARE(statusCode(reply.get()), 200);

    // Session doesn't exist anymore
    reply.reset(post(manager, url, toJson(jsonRequest(u"tools/list"_s, 2)), sessionId));
    QSignalSpy finishedSpy2(reply.get(), &QNetworkReply::finished);
    QVERIFY(finishedSpy2.wait());
    QCOMPARE(statusCode(reply.get()), 404);

    // Stopping server closes it
    QSignalSpy serverFinishedSpy(server.get(), &McpServerStreamHttpPluginInterface::finished);
    server->stop();
    QCOMPARE(serverFinishedSpy.count(), 1);
}

void McpServerStreamableHttpTest::shouldRejectRequestWithoutValidToken_data()
{
    QTest::addColumn<QByteArray>("authorization");
    QTest::newRow("missing") << QByteArray();
    QTest::newRow("wrong-token") << "Bearer wrong"_ba;
    QTest::newRow("token-prefix") << "Bearer secret"_ba;
    QTest::newRow("token-longer") << "Bearer secret-token-more"_ba;
    QTest::newRow("no-scheme") << "secret-token"_ba;
    QTest::newRow("basic-scheme") << "Basic secret-token"_ba;
    QTest::newRow("empty-bearer") << "Bearer "_ba;
}

void McpServerStreamableHttpTest::shouldRejectRequestWithoutValidToken()
{
    QFETCH(QByteArray, authorization);
    const QUrl url = freeUrl();
    auto server = createServer(url, "secret-token"_ba);
    QVERIFY(server);
    QSignalSpy serverReceivedSpy(server.get(), &McpServerStreamHttpPluginInterface::received);
    QNetworkAccessManager manager;

    std::unique_ptr<QNetworkReply> reply(post(manager, url, toJson(jsonRequest(u"initialize"_s, 1)), {}, authorization));
    QSignalSpy finishedSpy(reply.get(), &QNetworkReply::finished);
    QVERIFY(finishedSpy.wait());
    QCOMPARE(statusCode(reply.get()), 401);
    QCOMPARE(reply->rawHeader("WWW-Authenticate"_ba), "Bearer"_ba);
    QVERIFY(reply->rawHeader("Mcp-Session-Id"_ba).isEmpty());
    QCOMPARE(serverReceivedSpy.count(), 0);
}

void McpServerStreamableHttpTest::shouldAcceptRequestWithValidToken()
{
    const QUrl url = freeUrl();
    auto server = createServer(url, "secret-token"_ba);
    QVERIFY(server);
    QNetworkAccessManager manager;
    // Scheme is case insensitive
    const QByteArray authorization = "bearer secret-token"_ba;
    const QByteArray sessionId = initializeSession(manager, url, authorization);
    QVERIFY(!sessionId.isEmpty());

    std::unique_ptr<QNetworkReply> reply(post(manager, url, toJson(jsonRequest(u"tools/list"_s, 2)), sessionId, authorization));
    QSignalSpy finishedSpy(reply.get(), &QNetworkReply::finished);
    QVERIFY(finishedSpy.wait());
    QCOMPARE(statusCode(reply.get()), 200);

    // Valid session without token is rejected
    reply.reset(post(manager, url, toJson(jsonRequest(u"tools/list"_s, 3)), sessionId));
    QSignalSpy finishedSpy2(reply.get(), &QNetworkReply::finished);
    QVERIFY(finishedSpy2.wait());
    QCOMPARE(statusCode(reply.get()), 401);

    // DELETE needs token too
    QNetworkRequest deleteRequest(url);
    deleteRequest.setRawHeader("Mcp-Session-Id"_ba, sessionId);
    reply.reset(manager.deleteResource(deleteRequest));
    QSignalSpy finishedSpy3(reply.get(), &QNetworkReply::finished);
    QVERIFY(finishedSpy3.wait());
    QCOMPARE(statusCode(reply.get()), 401);
    deleteRequest.setRawHeader("Authorization"_ba, authorization);
    reply.reset(manager.deleteResource(deleteRequest));
    QSignalSpy finishedSpy4(reply.get(), &QNetworkReply::finished);
    QVERIFY(finishedSpy4.wait());
    QCOMPARE(statusCode(reply.get()), 200);
}

void McpServerStreamableHttpTest::shouldCheckOriginBeforeToken()
{
    const QUrl url = freeUrl();
    auto server = createServer(url, "secret-token"_ba);
    QVERIFY(server);
    QNetworkAccessManager manager;
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json"_ba);
    request.setRawHeader("Authorization"_ba, "Bearer secret-token"_ba);
    request.setRawHeader("Origin"_ba, "http://evil.example.com"_ba);
    std::unique_ptr<QNetworkReply> reply(manager.post(request, toJson(jsonRequest(u"initialize"_s, 1))));
    QSignalSpy finishedSpy(reply.get(), &QNetworkReply::finished);
    QVERIFY(finishedSpy.wait());
    QCOMPARE(statusCode(reply.get()), 403);
}

void McpServerStreamableHttpTest::shouldExchangeMessagesWithClientUsingToken()
{
    const QUrl url = freeUrl();
    auto server = createServer(url, "secret-token"_ba);
    QVERIFY(server);

    McpClientStreamableHttpPluginInterface client;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setServerUrl(url);
    settings.setHeaders({u"Authorization: Bearer secret-token"_s});
    client.setSettings(settings);
    QSignalSpy clientReceivedSpy(&client, &McpClientStreamableHttpPluginInterface::received);
    QSignalSpy clientErrorSpy(&client, &McpClientStreamableHttpPluginInterface::error);
    client.start();

    client.send(jsonRequest(u"initialize"_s, 1));
    QTRY_COMPARE(clientReceivedSpy.count(), 1);
    QCOMPARE(clientReceivedSpy.at(0).at(0).toJsonObject(), initializeResult(1));
    client.send(jsonNotification(u"notifications/initialized"_s));

    // Event stream (GET) is authorized too
    server->send(jsonNotification(u"notifications/tools/list_changed"_s));
    QTRY_COMPARE(clientReceivedSpy.count(), 2);
    QCOMPARE(clientReceivedSpy.at(1).at(0).toJsonObject(), jsonNotification(u"notifications/tools/list_changed"_s));
    QCOMPARE(clientErrorSpy.count(), 0);
}

void McpServerStreamableHttpTest::shouldExchangeMessagesWithClientUsingAuthToken()
{
    const QUrl url = freeUrl();
    auto server = createServer(url, "secret-token"_ba);
    QVERIFY(server);

    // Client and server use same setting
    McpClientStreamableHttpPluginInterface client;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setServerUrl(url);
    settings.setAuthToken("secret-token"_ba);
    client.setSettings(settings);
    QSignalSpy clientReceivedSpy(&client, &McpClientStreamableHttpPluginInterface::received);
    QSignalSpy clientErrorSpy(&client, &McpClientStreamableHttpPluginInterface::error);
    client.start();

    client.send(jsonRequest(u"initialize"_s, 1));
    QTRY_COMPARE(clientReceivedSpy.count(), 1);
    QCOMPARE(clientReceivedSpy.at(0).at(0).toJsonObject(), initializeResult(1));
    client.send(jsonNotification(u"notifications/initialized"_s));

    server->send(jsonNotification(u"notifications/tools/list_changed"_s));
    QTRY_COMPARE(clientReceivedSpy.count(), 2);
    QCOMPARE(clientReceivedSpy.at(1).at(0).toJsonObject(), jsonNotification(u"notifications/tools/list_changed"_s));
    QCOMPARE(clientErrorSpy.count(), 0);
}

void McpServerStreamableHttpTest::shouldRejectClientWithWrongAuthToken()
{
    const QUrl url = freeUrl();
    auto server = createServer(url, "secret-token"_ba);
    QVERIFY(server);
    QSignalSpy serverReceivedSpy(server.get(), &McpServerStreamHttpPluginInterface::received);

    McpClientStreamableHttpPluginInterface client;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setServerUrl(url);
    settings.setAuthToken("wrong-token"_ba);
    client.setSettings(settings);
    QSignalSpy clientReceivedSpy(&client, &McpClientStreamableHttpPluginInterface::received);
    client.start();

    client.send(jsonRequest(u"initialize"_s, 1));
    // Client creates an error response for its request
    QTRY_COMPARE(clientReceivedSpy.count(), 1);
    const QJsonObject response = clientReceivedSpy.at(0).at(0).toJsonObject();
    QCOMPARE(response.value("id"_L1).toInt(), 1);
    QVERIFY(response.contains("error"_L1));
    QCOMPARE(serverReceivedSpy.count(), 0);
}

#include "moc_mcpserverstreamablehttptest.cpp"
