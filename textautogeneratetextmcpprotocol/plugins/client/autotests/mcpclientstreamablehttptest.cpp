/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientstreamablehttptest.h"
#include "fakemcphttpserver.h"
#include "streamanblehttp/mcpclientstreamblehttpplugininterface.h"
#include <QJsonDocument>
#include <QSignalSpy>
#include <QTcpSocket>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpClientStreamableHttpTest)

namespace
{
const QByteArray sessionId = "session-42"_ba;

QJsonObject jsonRequest(const QString &method, int id)
{
    return QJsonObject{{"jsonrpc"_L1, u"2.0"_s}, {"id"_L1, id}, {"method"_L1, method}};
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
                              {"serverInfo"_L1, QJsonObject{{"name"_L1, u"fake"_s}, {"version"_L1, u"1"_s}}}});
}

// Answer initialize and notifications, GET stream is not supported (405)
bool handleDefault(const FakeMcpHttpServer::Request &request, QTcpSocket *socket)
{
    if (request.method == "GET") {
        FakeMcpHttpServer::sendResponse(socket, 405);
        return true;
    }
    if (request.method == "DELETE") {
        FakeMcpHttpServer::sendResponse(socket, 200);
        return true;
    }
    const QJsonObject obj = request.json();
    if (obj.value("method"_L1).toString() == "initialize"_L1) {
        FakeMcpHttpServer::sendResponse(socket,
                                        200,
                                        "application/json",
                                        QJsonDocument(initializeResult(obj.value("id"_L1))).toJson(QJsonDocument::Compact),
                                        {{"Mcp-Session-Id"_ba, sessionId}});
        return true;
    }
    if (!obj.contains("id"_L1)) {
        // Notification
        FakeMcpHttpServer::sendResponse(socket, 202);
        return true;
    }
    return false;
}

void initialize(McpClientStreambleHttpPluginInterface &client, FakeMcpHttpServer &server)
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setServerUrl(server.url(u"/mcp"_s));
    settings.setHeaders({u"Authorization: Bearer token"_s});
    client.setSettings(settings);
    QSignalSpy startedSpy(&client, &McpClientStreambleHttpPluginInterface::started);
    QSignalSpy receivedSpy(&client, &McpClientStreambleHttpPluginInterface::received);
    client.start();
    QCOMPARE(startedSpy.count(), 1);
    client.send(jsonRequest(u"initialize"_s, 1));
    // Event stream can send messages just after initialize
    QTRY_VERIFY(receivedSpy.count() >= 1);
    QCOMPARE(receivedSpy.at(0).at(0).toJsonObject().value("id"_L1).toInt(), 1);
}

QList<QJsonObject> receivedMessages(const QSignalSpy &spy)
{
    QList<QJsonObject> messages;
    for (const auto &args : spy) {
        messages.append(args.at(0).toJsonObject());
    }
    return messages;
}
}

McpClientStreamableHttpTest::McpClientStreamableHttpTest(QObject *parent)
    : QObject{parent}
{
}

void McpClientStreamableHttpTest::shouldNotStartWithInvalidUrl()
{
    McpClientStreambleHttpPluginInterface client;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setServerUrl(QUrl(u"ftp://foo"_s));
    client.setSettings(settings);
    QSignalSpy startedSpy(&client, &McpClientStreambleHttpPluginInterface::started);
    QSignalSpy errorSpy(&client, &McpClientStreambleHttpPluginInterface::error);
    QSignalSpy finishedSpy(&client, &McpClientStreambleHttpPluginInterface::finished);
    client.start();
    QCOMPARE(startedSpy.count(), 0);
    QCOMPARE(errorSpy.count(), 1);
    QCOMPARE(finishedSpy.count(), 1);
}

void McpClientStreamableHttpTest::shouldUseSessionAndProtocolVersion()
{
    FakeMcpHttpServer server;
    server.setHandler([](const FakeMcpHttpServer::Request &request, QTcpSocket *socket) {
        if (handleDefault(request, socket)) {
            return;
        }
        // Answer in a SSE stream, with a server request before response
        const QJsonObject ping = jsonRequest(u"ping"_s, 99);
        FakeMcpHttpServer::sendEventStream(socket, FakeMcpHttpServer::jsonEvent(ping) + FakeMcpHttpServer::jsonEvent(result(request.json().value("id"_L1))));
    });
    McpClientStreambleHttpPluginInterface client;
    initialize(client, server);
    QSignalSpy receivedSpy(&client, &McpClientStreambleHttpPluginInterface::received);
    client.send(QJsonObject{{"jsonrpc"_L1, u"2.0"_s}, {"method"_L1, u"notifications/initialized"_s}});
    client.send(jsonRequest(u"tools/list"_s, 2));
    QTRY_COMPARE(receivedSpy.count(), 2);
    const QList<QJsonObject> messages = receivedMessages(receivedSpy);
    QCOMPARE(messages.at(0).value("method"_L1).toString(), u"ping"_s);
    QCOMPARE(messages.at(1).value("id"_L1).toInt(), 2);

    const auto posts = server.requests("POST");
    QCOMPARE(posts.count(), 3);
    // initialize: no session yet
    QVERIFY(posts.at(0).header("Mcp-Session-Id").isEmpty());
    QVERIFY(posts.at(0).header("MCP-Protocol-Version").isEmpty());
    for (const auto &post : posts) {
        QCOMPARE(post.header("Accept"), "application/json, text/event-stream"_ba);
        QCOMPARE(post.header("Content-Type"), "application/json"_ba);
        QCOMPARE(post.header("Authorization"), "Bearer token"_ba);
    }
    for (qsizetype i = 1; i < posts.count(); ++i) {
        QCOMPARE(posts.at(i).header("Mcp-Session-Id"), sessionId);
        QCOMPARE(posts.at(i).header("MCP-Protocol-Version"), "2025-11-25"_ba);
    }
}

void McpClientStreamableHttpTest::shouldResumeInterruptedStream()
{
    FakeMcpHttpServer server;
    QJsonValue pendingId;
    server.setHandler([&pendingId](const FakeMcpHttpServer::Request &request, QTcpSocket *socket) {
        if (request.method == "GET" && request.header("Last-Event-ID") == "event-1") {
            FakeMcpHttpServer::sendEventStream(socket, FakeMcpHttpServer::jsonEvent(result(pendingId), "event-2"));
            return;
        }
        if (handleDefault(request, socket)) {
            return;
        }
        // Close stream before sending response
        pendingId = request.json().value("id"_L1);
        const QJsonObject progress{{"jsonrpc"_L1, u"2.0"_s}, {"method"_L1, u"notifications/progress"_s}};
        FakeMcpHttpServer::sendEventStream(socket, "retry: 10\n" + FakeMcpHttpServer::jsonEvent(progress, "event-1"));
    });
    McpClientStreambleHttpPluginInterface client;
    initialize(client, server);
    QSignalSpy receivedSpy(&client, &McpClientStreambleHttpPluginInterface::received);
    QSignalSpy errorSpy(&client, &McpClientStreambleHttpPluginInterface::error);
    client.send(jsonRequest(u"tools/list"_s, 2));
    QTRY_COMPARE(receivedSpy.count(), 2);
    const QList<QJsonObject> messages = receivedMessages(receivedSpy);
    QCOMPARE(messages.at(0).value("method"_L1).toString(), u"notifications/progress"_s);
    QCOMPARE(messages.at(1), result(2));
    QCOMPARE(errorSpy.count(), 0);
}

void McpClientStreamableHttpTest::shouldCreateErrorResponseWhenStreamCantBeResumed()
{
    FakeMcpHttpServer server;
    server.setHandler([](const FakeMcpHttpServer::Request &request, QTcpSocket *socket) {
        if (handleDefault(request, socket)) {
            return;
        }
        // No event id: stream can't be resumed
        FakeMcpHttpServer::sendEventStream(socket, ": keep-alive\n\n");
    });
    McpClientStreambleHttpPluginInterface client;
    initialize(client, server);
    QSignalSpy receivedSpy(&client, &McpClientStreambleHttpPluginInterface::received);
    QSignalSpy errorSpy(&client, &McpClientStreambleHttpPluginInterface::error);
    client.send(QJsonObject{{"jsonrpc"_L1, u"2.0"_s}, {"id"_L1, u"string-id"_s}, {"method"_L1, u"tools/list"_s}});
    QTRY_COMPARE(receivedSpy.count(), 1);
    const QJsonObject response = receivedSpy.at(0).at(0).toJsonObject();
    QCOMPARE(response.value("id"_L1).toString(), u"string-id"_s);
    QCOMPARE(response.value("error"_L1).toObject().value("code"_L1).toInt(), -32000);
    QCOMPARE(errorSpy.count(), 1);
}

void McpClientStreamableHttpTest::shouldCreateErrorResponseWhenPostFailed()
{
    FakeMcpHttpServer server;
    server.setHandler([](const FakeMcpHttpServer::Request &request, QTcpSocket *socket) {
        if (handleDefault(request, socket)) {
            return;
        }
        FakeMcpHttpServer::sendResponse(socket, 500);
    });
    McpClientStreambleHttpPluginInterface client;
    initialize(client, server);
    QSignalSpy receivedSpy(&client, &McpClientStreambleHttpPluginInterface::received);
    client.send(jsonRequest(u"tools/list"_s, 2));
    QTRY_COMPARE(receivedSpy.count(), 1);
    const QJsonObject response = receivedSpy.at(0).at(0).toJsonObject();
    QCOMPARE(response.value("id"_L1).toInt(), 2);
    QCOMPARE(response.value("error"_L1).toObject().value("code"_L1).toInt(), -32000);
}

void McpClientStreamableHttpTest::shouldFinishWhenSessionExpired()
{
    FakeMcpHttpServer server;
    server.setHandler([](const FakeMcpHttpServer::Request &request, QTcpSocket *socket) {
        if (handleDefault(request, socket)) {
            return;
        }
        FakeMcpHttpServer::sendResponse(socket, 404);
    });
    McpClientStreambleHttpPluginInterface client;
    initialize(client, server);
    QSignalSpy errorSpy(&client, &McpClientStreambleHttpPluginInterface::error);
    QSignalSpy finishedSpy(&client, &McpClientStreambleHttpPluginInterface::finished);
    client.send(jsonRequest(u"tools/list"_s, 2));
    QTRY_COMPARE(finishedSpy.count(), 1);
    QCOMPARE(errorSpy.count(), 1);

    // Client can be restarted
    QSignalSpy startedSpy(&client, &McpClientStreambleHttpPluginInterface::started);
    client.start();
    QCOMPARE(startedSpy.count(), 1);
}

void McpClientStreamableHttpTest::shouldDeleteSessionWhenStopped()
{
    FakeMcpHttpServer server;
    server.setHandler([](const FakeMcpHttpServer::Request &request, QTcpSocket *socket) {
        handleDefault(request, socket);
    });
    McpClientStreambleHttpPluginInterface client;
    initialize(client, server);
    QSignalSpy finishedSpy(&client, &McpClientStreambleHttpPluginInterface::finished);
    client.stop();
    QCOMPARE(finishedSpy.count(), 1);
    QTRY_COMPARE(server.requests("DELETE").count(), 1);
    QCOMPARE(server.requests("DELETE").at(0).header("Mcp-Session-Id"), sessionId);
    // Already stopped
    client.stop();
    QCOMPARE(finishedSpy.count(), 1);
}

void McpClientStreamableHttpTest::shouldReconnectEventStream()
{
    FakeMcpHttpServer server;
    server.setHandler([](const FakeMcpHttpServer::Request &request, QTcpSocket *socket) {
        if (request.method == "GET") {
            if (request.header("Last-Event-ID").isEmpty()) {
                const QJsonObject notification{{"jsonrpc"_L1, u"2.0"_s}, {"method"_L1, u"notifications/tools/list_changed"_s}};
                FakeMcpHttpServer::sendEventStream(socket, "retry: 10\n" + FakeMcpHttpServer::jsonEvent(notification, "get-1"));
            } else {
                // Stop reconnection
                FakeMcpHttpServer::sendResponse(socket, 405);
            }
            return;
        }
        handleDefault(request, socket);
    });
    McpClientStreambleHttpPluginInterface client;
    QSignalSpy receivedSpy(&client, &McpClientStreambleHttpPluginInterface::received);
    initialize(client, server);
    // Event stream is opened after initialize
    QTRY_COMPARE(server.requests("GET").count(), 2);
    QTRY_COMPARE(receivedSpy.count(), 2);
    QCOMPARE(receivedSpy.at(1).at(0).toJsonObject().value("method"_L1).toString(), u"notifications/tools/list_changed"_s);
    const auto gets = server.requests("GET");
    QCOMPARE(gets.at(0).header("Accept"), "text/event-stream"_ba);
    QCOMPARE(gets.at(0).header("Mcp-Session-Id"), sessionId);
    QCOMPARE(gets.at(1).header("Last-Event-ID"), "get-1"_ba);
    // 405: no more reconnection
    QTest::qWait(100);
    QCOMPARE(server.requests("GET").count(), 2);
}

#include "moc_mcpclientstreamablehttptest.cpp"
