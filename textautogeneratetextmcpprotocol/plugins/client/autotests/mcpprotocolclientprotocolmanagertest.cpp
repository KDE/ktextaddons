/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolclientprotocolmanagertest.h"
#include "fakemcphttpserver.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QSignalSpy>
#include <QTcpSocket>
#include <QTest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCallToolResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolClientProtocolManager>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolGetPromptResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolReadResourceResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTextContent>
using namespace Qt::Literals::StringLiterals;
using TextAutoGenerateTextMcpProtocolCore::McpProtocolClientProtocolManager;
QTEST_GUILESS_MAIN(McpProtocolClientProtocolManagerTest)

namespace
{
QJsonObject result(const QJsonValue &id, const QJsonObject &result = {})
{
    return QJsonObject{{"jsonrpc"_L1, u"2.0"_s}, {"id"_L1, id}, {"result"_L1, result}};
}

void sendJson(QTcpSocket *socket, const QJsonObject &obj)
{
    FakeMcpHttpServer::sendResponse(socket, 200, "application/json", QJsonDocument(obj).toJson(QJsonDocument::Compact));
}

// Simple server: initialize with \a protocolVersion, other requests are handled by \a handler
FakeMcpHttpServer::Handler createHandler(
    const QString &protocolVersion = u"2025-11-25"_s,
    const std::function<void(const QJsonObject &, QTcpSocket *)> &handler =
        [](const QJsonObject &obj, QTcpSocket *socket) {
            sendJson(socket, result(obj.value("id"_L1), QJsonObject{{"tools"_L1, QJsonArray{}}}));
        },
    const QJsonObject &capabilities = QJsonObject{{"tools"_L1, QJsonObject{}}})
{
    return [protocolVersion, handler, capabilities](const FakeMcpHttpServer::Request &request, QTcpSocket *socket) {
        if (request.method != "POST") {
            FakeMcpHttpServer::sendResponse(socket, 405);
            return;
        }
        const QJsonObject obj = request.json();
        const QString method = obj.value("method"_L1).toString();
        if (method == "initialize"_L1) {
            sendJson(socket,
                     result(obj.value("id"_L1),
                            QJsonObject{{"protocolVersion"_L1, protocolVersion},
                                        {"capabilities"_L1, capabilities},
                                        {"serverInfo"_L1, QJsonObject{{"name"_L1, u"fake"_s}, {"version"_L1, u"1"_s}}}}));
        } else if (!obj.contains("id"_L1) || !obj.contains("method"_L1)) {
            // Notification or response
            FakeMcpHttpServer::sendResponse(socket, 202);
        } else {
            handler(obj, socket);
        }
    };
}

TextAutoGenerateTextMcpProtocolCore::McpServer createServer(const FakeMcpHttpServer &fakeServer)
{
    TextAutoGenerateTextMcpProtocolCore::McpServer server;
    server.setName(u"test"_s);
    server.createUniqueIdentifier();
    server.setTransportType(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::StreamableHttp);
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setServerUrl(fakeServer.url(u"/mcp"_s));
    server.setSettings(settings);
    return server;
}

QList<QJsonObject> postedMessages(const FakeMcpHttpServer &server, const QString &method)
{
    QList<QJsonObject> messages;
    for (const auto &request : server.requests("POST")) {
        if (request.json().value("method"_L1).toString() == method) {
            messages.append(request.json());
        }
    }
    return messages;
}

void initialize(McpProtocolClientProtocolManager &manager)
{
    const QSignalSpy initializedSpy(&manager, &McpProtocolClientProtocolManager::initialized);
    manager.initializeClient();
    QTRY_COMPARE(initializedSpy.count(), 1);
    QVERIFY(manager.isInitialized());
}
}

McpProtocolClientProtocolManagerTest::McpProtocolClientProtocolManagerTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolClientProtocolManagerTest::shouldInitializeAndListTools()
{
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler());
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    // Requests are refused before initialize
    QCOMPARE(manager.executeAction(McpProtocolClientProtocolManager::MethodType::ListTools), -1);
    initialize(manager);
    QCOMPARE(manager.initializeResult().protocolVersion(), u"2025-11-25"_s);
    QTRY_COMPARE(postedMessages(fakeServer, u"notifications/initialized"_s).count(), 1);
    const QJsonObject initialize = postedMessages(fakeServer, u"initialize"_s).constFirst();
    QCOMPARE(initialize.value("params"_L1).toObject().value("protocolVersion"_L1).toString(), u"2025-11-25"_s);
    QVERIFY(!initialize.value("params"_L1).toObject().value("clientInfo"_L1).toObject().value("name"_L1).toString().isEmpty());

    const QSignalSpy receivedSpy(&manager, &McpProtocolClientProtocolManager::received);
    const qint64 identifier = manager.executeAction(McpProtocolClientProtocolManager::MethodType::ListTools);
    QVERIFY(identifier > 0);
    QTRY_COMPARE(receivedSpy.count(), 1);
    QCOMPARE(receivedSpy.at(0).at(1).value<McpProtocolClientProtocolManager::MethodType>(), McpProtocolClientProtocolManager::MethodType::ListTools);
    QCOMPARE(receivedSpy.at(0).at(0).toJsonObject().value("id"_L1).toInteger(), identifier);
}

void McpProtocolClientProtocolManagerTest::shouldAnnounceElicitationCapability()
{
    {
        // Not announced by default
        FakeMcpHttpServer fakeServer;
        fakeServer.setHandler(createHandler());
        McpProtocolClientProtocolManager manager(createServer(fakeServer));
        QVERIFY(!manager.elicitationSupported());
        initialize(manager);
        const QJsonObject initialize = postedMessages(fakeServer, u"initialize"_s).constFirst();
        QVERIFY(!initialize.value("params"_L1).toObject().value("capabilities"_L1).toObject().contains("elicitation"_L1));
    }
    {
        FakeMcpHttpServer fakeServer;
        fakeServer.setHandler(createHandler());
        McpProtocolClientProtocolManager manager(createServer(fakeServer));
        manager.setElicitationSupported(true);
        QVERIFY(manager.elicitationSupported());
        initialize(manager);
        const QJsonObject initialize = postedMessages(fakeServer, u"initialize"_s).constFirst();
        const QJsonObject capabilities = initialize.value("params"_L1).toObject().value("capabilities"_L1).toObject();
        QCOMPARE(capabilities.value("elicitation"_L1).toObject(), QJsonObject({{"form"_L1, QJsonObject()}}));
    }
}

void McpProtocolClientProtocolManagerTest::shouldAnswerServerRequests()
{
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler(u"2025-11-25"_s, [](const QJsonObject &obj, QTcpSocket *socket) {
        // Server sends requests before response
        const QJsonObject ping{{"jsonrpc"_L1, u"2.0"_s}, {"id"_L1, u"srv-1"_s}, {"method"_L1, u"ping"_s}};
        const QJsonObject roots{{"jsonrpc"_L1, u"2.0"_s}, {"id"_L1, u"srv-2"_s}, {"method"_L1, u"roots/list"_s}};
        FakeMcpHttpServer::sendEventStream(socket,
                                           FakeMcpHttpServer::jsonEvent(ping) + FakeMcpHttpServer::jsonEvent(roots)
                                               + FakeMcpHttpServer::jsonEvent(result(obj.value("id"_L1))));
    }));
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    initialize(manager);
    manager.executeAction(McpProtocolClientProtocolManager::MethodType::ListTools);
    // Find responses of client
    QList<QJsonObject> responses;
    QTRY_VERIFY([&]() {
        responses.clear();
        for (const auto &request : fakeServer.requests("POST")) {
            const QJsonObject obj = request.json();
            if (!obj.contains("method"_L1)) {
                responses.append(obj);
            }
        }
        return responses.count() == 2;
    }());
    for (const auto &response : std::as_const(responses)) {
        if (response.value("id"_L1).toString() == u"srv-1"_s) {
            QCOMPARE(response.value("result"_L1).toObject(), QJsonObject());
        } else {
            QCOMPARE(response.value("id"_L1).toString(), u"srv-2"_s);
            QCOMPARE(response.value("error"_L1).toObject().value("code"_L1).toInt(), -32601);
        }
    }
}

void McpProtocolClientProtocolManagerTest::shouldRejectUnsupportedProtocolVersion()
{
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler(u"1999-01-01"_s));
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    const QSignalSpy errorSpy(&manager, &McpProtocolClientProtocolManager::error);
    const QSignalSpy initializedSpy(&manager, &McpProtocolClientProtocolManager::initialized);
    manager.initializeClient();
    QTRY_COMPARE(errorSpy.count(), 1);
    QCOMPARE(initializedSpy.count(), 0);
    QVERIFY(!manager.isInitialized());
}

void McpProtocolClientProtocolManagerTest::shouldCancelRequestWhenTimeoutExpired()
{
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler(u"2025-11-25"_s, [](const QJsonObject &, QTcpSocket *) {
        // Never answer
    }));
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    manager.setRequestTimeout(std::chrono::milliseconds(200));
    initialize(manager);
    const QSignalSpy receivedSpy(&manager, &McpProtocolClientProtocolManager::received);
    const qint64 identifier = manager.executeAction(McpProtocolClientProtocolManager::MethodType::ListTools);
    QTRY_COMPARE(receivedSpy.count(), 1);
    QCOMPARE(receivedSpy.at(0).at(1).value<McpProtocolClientProtocolManager::MethodType>(), McpProtocolClientProtocolManager::MethodType::ListTools);
    const QJsonObject response = receivedSpy.at(0).at(0).toJsonObject();
    QCOMPARE(response.value("id"_L1).toInteger(), identifier);
    QCOMPARE(response.value("error"_L1).toObject().value("code"_L1).toInt(), -32001);
    // Server is informed
    QTRY_COMPARE(postedMessages(fakeServer, u"notifications/cancelled"_s).count(), 1);
    const QJsonObject params = postedMessages(fakeServer, u"notifications/cancelled"_s).constFirst().value("params"_L1).toObject();
    QCOMPARE(params.value("requestId"_L1).toInteger(), identifier);
}

void McpProtocolClientProtocolManagerTest::shouldCancelRequest()
{
    FakeMcpHttpServer fakeServer;
    QList<QTcpSocket *> pendingSockets;
    fakeServer.setHandler(createHandler(u"2025-11-25"_s, [&pendingSockets](const QJsonObject &, QTcpSocket *socket) {
        pendingSockets.append(socket);
    }));
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    initialize(manager);
    const QSignalSpy receivedSpy(&manager, &McpProtocolClientProtocolManager::received);
    const qint64 identifier = manager.executeAction(McpProtocolClientProtocolManager::MethodType::ListTools);
    QTRY_COMPARE(pendingSockets.count(), 1);
    manager.cancelRequest(identifier, u"User cancelled"_s);
    QTRY_COMPARE(postedMessages(fakeServer, u"notifications/cancelled"_s).count(), 1);
    const QJsonObject params = postedMessages(fakeServer, u"notifications/cancelled"_s).constFirst().value("params"_L1).toObject();
    QCOMPARE(params.value("requestId"_L1).toInteger(), identifier);
    QCOMPARE(params.value("reason"_L1).toString(), u"User cancelled"_s);
    // Response received after cancellation is ignored
    sendJson(pendingSockets.constFirst(), result(identifier));
    QTest::qWait(100);
    QCOMPARE(receivedSpy.count(), 1);
    QCOMPARE(receivedSpy.at(0).at(1).value<McpProtocolClientProtocolManager::MethodType>(), McpProtocolClientProtocolManager::MethodType::Unknown);
}

void McpProtocolClientProtocolManagerTest::shouldRestartAfterStop()
{
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler());
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    initialize(manager);
    const QSignalSpy finishedSpy(&manager, &McpProtocolClientProtocolManager::finished);
    manager.stopClient();
    QTRY_COMPARE(finishedSpy.count(), 1);
    QVERIFY(!manager.isInitialized());
    initialize(manager);
    QCOMPARE(postedMessages(fakeServer, u"initialize"_s).count(), 2);
}

void McpProtocolClientProtocolManagerTest::shouldCallTool()
{
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler(u"2025-11-25"_s, [](const QJsonObject &obj, QTcpSocket *socket) {
        const QJsonObject params = obj.value("params"_L1).toObject();
        const QString text = u"%1:%2"_s.arg(params.value("name"_L1).toString(), params.value("arguments"_L1).toObject().value("city"_L1).toString());
        const QJsonObject content{{"type"_L1, u"text"_s}, {"text"_L1, text}};
        sendJson(socket, result(obj.value("id"_L1), QJsonObject{{"content"_L1, QJsonArray{content}}, {"isError"_L1, false}}));
    }));
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    // Not initialized
    QCOMPARE(manager.callTool(u"weather"_s), -1);
    initialize(manager);
    QCOMPARE(manager.callTool(QString()), -1);

    const QSignalSpy receivedSpy(&manager, &McpProtocolClientProtocolManager::received);
    const qint64 identifier = manager.callTool(u"weather"_s, QJsonObject{{"city"_L1, u"Paris"_s}});
    QVERIFY(identifier > 0);
    QTRY_COMPARE(receivedSpy.count(), 1);
    QCOMPARE(receivedSpy.at(0).at(1).value<McpProtocolClientProtocolManager::MethodType>(), McpProtocolClientProtocolManager::MethodType::CallTool);
    const QJsonObject response = receivedSpy.at(0).at(0).toJsonObject();
    QCOMPARE(response.value("id"_L1).toInteger(), identifier);
    const auto callToolResult = TextAutoGenerateTextMcpProtocolCore::McpProtocolCallToolResult::fromJson(response.value("result"_L1).toObject());
    QCOMPARE(callToolResult.content().count(), 1);
    const auto text = std::get_if<TextAutoGenerateTextMcpProtocolCore::McpProtocolTextContent>(&callToolResult.content().at(0));
    QVERIFY(text);
    QCOMPARE(text->text(), u"weather:Paris"_s);

    const QJsonObject request = postedMessages(fakeServer, u"tools/call"_s).constFirst();
    QCOMPARE(request.value("params"_L1).toObject().value("name"_L1).toString(), u"weather"_s);
}

void McpProtocolClientProtocolManagerTest::shouldNotCallToolWhenServerDoesNotSupportTools()
{
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler(
        u"2025-11-25"_s,
        [](const QJsonObject &obj, QTcpSocket *socket) {
            sendJson(socket, result(obj.value("id"_L1)));
        },
        QJsonObject{}));
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    initialize(manager);
    QCOMPARE(manager.callTool(u"weather"_s), -1);
    QCOMPARE(manager.executeAction(McpProtocolClientProtocolManager::MethodType::ListTools), -1);
    QCOMPARE(manager.executeAction(McpProtocolClientProtocolManager::MethodType::ListPrompts), -1);
    QCOMPARE(manager.executeAction(McpProtocolClientProtocolManager::MethodType::ResourceTemplates), -1);
    QCOMPARE(manager.executeAction(McpProtocolClientProtocolManager::MethodType::ListResources), -1);
    // Ping is always allowed
    QVERIFY(manager.executeAction(McpProtocolClientProtocolManager::MethodType::Ping) > 0);
    QTest::qWait(100);
    QVERIFY(postedMessages(fakeServer, u"tools/call"_s).isEmpty());
}

void McpProtocolClientProtocolManagerTest::shouldGetPrompt()
{
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler(
        u"2025-11-25"_s,
        [](const QJsonObject &obj, QTcpSocket *socket) {
            const QJsonObject params = obj.value("params"_L1).toObject();
            const QString text = u"%1:%2"_s.arg(params.value("name"_L1).toString(), params.value("arguments"_L1).toObject().value("code"_L1).toString());
            const QJsonObject message{{"role"_L1, u"user"_s}, {"content"_L1, QJsonObject{{"type"_L1, u"text"_s}, {"text"_L1, text}}}};
            sendJson(socket, result(obj.value("id"_L1), QJsonObject{{"description"_L1, u"Review code"_s}, {"messages"_L1, QJsonArray{message}}}));
        },
        QJsonObject{{"prompts"_L1, QJsonObject{}}}));
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    // Not initialized
    QCOMPARE(manager.getPrompt(u"review"_s), -1);
    initialize(manager);
    QCOMPARE(manager.getPrompt(QString()), -1);
    // Prompts are not tools
    QCOMPARE(manager.executeAction(McpProtocolClientProtocolManager::MethodType::GetPrompt), -1);

    const QSignalSpy receivedSpy(&manager, &McpProtocolClientProtocolManager::received);
    const qint64 identifier = manager.getPrompt(u"review"_s, {{u"code"_s, u"foo()"_s}});
    QVERIFY(identifier > 0);
    QTRY_COMPARE(receivedSpy.count(), 1);
    QCOMPARE(receivedSpy.at(0).at(1).value<McpProtocolClientProtocolManager::MethodType>(), McpProtocolClientProtocolManager::MethodType::GetPrompt);
    const QJsonObject response = receivedSpy.at(0).at(0).toJsonObject();
    QCOMPARE(response.value("id"_L1).toInteger(), identifier);
    // Not a paginated response: result is unchanged
    const QJsonObject resultObj = response.value("result"_L1).toObject();
    QCOMPARE(resultObj.keys(), (QStringList{u"description"_s, u"messages"_s}));
    const auto getPromptResult = TextAutoGenerateTextMcpProtocolCore::McpProtocolGetPromptResult::fromJson(resultObj);
    QCOMPARE(getPromptResult.messages().count(), 1);

    const QJsonObject request = postedMessages(fakeServer, u"prompts/get"_s).constFirst();
    const QJsonObject params = request.value("params"_L1).toObject();
    QCOMPARE(params.value("name"_L1).toString(), u"review"_s);
    QCOMPARE(params.value("arguments"_L1).toObject(), (QJsonObject{{"code"_L1, u"foo()"_s}}));
}

void McpProtocolClientProtocolManagerTest::shouldNotGetPromptWhenServerDoesNotSupportPrompts()
{
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler());
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    initialize(manager);
    QCOMPARE(manager.getPrompt(u"review"_s), -1);
    QTest::qWait(100);
    QVERIFY(postedMessages(fakeServer, u"prompts/get"_s).isEmpty());
}

void McpProtocolClientProtocolManagerTest::shouldReadResource()
{
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler(
        u"2025-11-25"_s,
        [](const QJsonObject &obj, QTcpSocket *socket) {
            const QString uri = obj.value("params"_L1).toObject().value("uri"_L1).toString();
            const QJsonObject contents{{"uri"_L1, uri}, {"mimeType"_L1, u"text/plain"_s}, {"text"_L1, u"hello"_s}};
            sendJson(socket, result(obj.value("id"_L1), QJsonObject{{"contents"_L1, QJsonArray{contents}}}));
        },
        QJsonObject{{"resources"_L1, QJsonObject{}}}));
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    // Not initialized
    QCOMPARE(manager.readResource(u"file:///foo.txt"_s), -1);
    initialize(manager);
    QCOMPARE(manager.readResource(QString()), -1);
    // Use readResource()
    QCOMPARE(manager.executeAction(McpProtocolClientProtocolManager::MethodType::ReadResource), -1);

    const QSignalSpy receivedSpy(&manager, &McpProtocolClientProtocolManager::received);
    const qint64 identifier = manager.readResource(u"file:///foo.txt"_s);
    QVERIFY(identifier > 0);
    QTRY_COMPARE(receivedSpy.count(), 1);
    QCOMPARE(receivedSpy.at(0).at(1).value<McpProtocolClientProtocolManager::MethodType>(), McpProtocolClientProtocolManager::MethodType::ReadResource);
    const QJsonObject response = receivedSpy.at(0).at(0).toJsonObject();
    QCOMPARE(response.value("id"_L1).toInteger(), identifier);
    // Not a paginated response: result is unchanged
    const QJsonObject resultObj = response.value("result"_L1).toObject();
    QCOMPARE(resultObj.keys(), (QStringList{u"contents"_s}));
    const auto readResourceResult = TextAutoGenerateTextMcpProtocolCore::McpProtocolReadResourceResult::fromJson(resultObj);
    QCOMPARE(readResourceResult.contents().count(), 1);

    const QJsonObject request = postedMessages(fakeServer, u"resources/read"_s).constFirst();
    QCOMPARE(request.value("params"_L1).toObject().value("uri"_L1).toString(), u"file:///foo.txt"_s);
}

void McpProtocolClientProtocolManagerTest::shouldNotReadResourceWhenServerDoesNotSupportResources()
{
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler());
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    initialize(manager);
    QCOMPARE(manager.readResource(u"file:///foo.txt"_s), -1);
    QTest::qWait(100);
    QVERIFY(postedMessages(fakeServer, u"resources/read"_s).isEmpty());
}

namespace
{
QJsonObject tool(const QString &name)
{
    return QJsonObject{{"name"_L1, name}, {"inputSchema"_L1, QJsonObject{{"type"_L1, u"object"_s}}}};
}

QStringList toolNames(const QJsonObject &response)
{
    QStringList names;
    const QJsonArray tools = response.value("result"_L1).toObject().value("tools"_L1).toArray();
    for (const auto &t : tools) {
        names.append(t.toObject().value("name"_L1).toString());
    }
    return names;
}
}

void McpProtocolClientProtocolManagerTest::shouldFetchAllPages()
{
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler(u"2025-11-25"_s, [](const QJsonObject &obj, QTcpSocket *socket) {
        const QString cursor = obj.value("params"_L1).toObject().value("cursor"_L1).toString();
        QJsonObject page;
        if (cursor.isEmpty()) {
            page = QJsonObject{{"tools"_L1, QJsonArray{tool(u"a"_s), tool(u"b"_s)}}, {"nextCursor"_L1, u"c1"_s}};
        } else if (cursor == u"c1"_s) {
            page = QJsonObject{{"tools"_L1, QJsonArray{tool(u"c"_s)}}, {"nextCursor"_L1, u"c2"_s}};
        } else {
            page = QJsonObject{{"tools"_L1, QJsonArray{tool(u"d"_s)}}};
        }
        sendJson(socket, result(obj.value("id"_L1), page));
    }));
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    initialize(manager);
    const QSignalSpy receivedSpy(&manager, &McpProtocolClientProtocolManager::received);
    const qint64 identifier = manager.executeAction(McpProtocolClientProtocolManager::MethodType::ListTools);
    QTRY_COMPARE(receivedSpy.count(), 1);
    QTest::qWait(100);
    // Only one response with all pages
    QCOMPARE(receivedSpy.count(), 1);
    QCOMPARE(receivedSpy.at(0).at(1).value<McpProtocolClientProtocolManager::MethodType>(), McpProtocolClientProtocolManager::MethodType::ListTools);
    const QJsonObject response = receivedSpy.at(0).at(0).toJsonObject();
    QCOMPARE(response.value("id"_L1).toInteger(), identifier);
    QCOMPARE(toolNames(response), QStringList({u"a"_s, u"b"_s, u"c"_s, u"d"_s}));
    QVERIFY(!response.value("result"_L1).toObject().contains("nextCursor"_L1));

    const auto requests = postedMessages(fakeServer, u"tools/list"_s);
    QCOMPARE(requests.count(), 3);
    QVERIFY(!requests.at(0).contains("params"_L1));
    QCOMPARE(requests.at(1).value("params"_L1).toObject().value("cursor"_L1).toString(), u"c1"_s);
    QCOMPARE(requests.at(2).value("params"_L1).toObject().value("cursor"_L1).toString(), u"c2"_s);
}

void McpProtocolClientProtocolManagerTest::shouldStopPaginationWhenCursorDoesNotChange()
{
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler(u"2025-11-25"_s, [](const QJsonObject &obj, QTcpSocket *socket) {
        sendJson(socket, result(obj.value("id"_L1), QJsonObject{{"tools"_L1, QJsonArray{tool(u"a"_s)}}, {"nextCursor"_L1, u"same"_s}}));
    }));
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    initialize(manager);
    const QSignalSpy receivedSpy(&manager, &McpProtocolClientProtocolManager::received);
    manager.executeAction(McpProtocolClientProtocolManager::MethodType::ListTools);
    QTRY_COMPARE(receivedSpy.count(), 1);
    QCOMPARE(postedMessages(fakeServer, u"tools/list"_s).count(), 2);
    QCOMPARE(toolNames(receivedSpy.at(0).at(0).toJsonObject()), QStringList({u"a"_s, u"a"_s}));
}

void McpProtocolClientProtocolManagerTest::shouldReturnErrorOfPage()
{
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler(u"2025-11-25"_s, [](const QJsonObject &obj, QTcpSocket *socket) {
        if (obj.value("params"_L1).toObject().value("cursor"_L1).toString().isEmpty()) {
            sendJson(socket, result(obj.value("id"_L1), QJsonObject{{"tools"_L1, QJsonArray{tool(u"a"_s)}}, {"nextCursor"_L1, u"c1"_s}}));
        } else {
            const QJsonObject error{{"code"_L1, -32602}, {"message"_L1, u"Invalid cursor"_s}};
            sendJson(socket, QJsonObject{{"jsonrpc"_L1, u"2.0"_s}, {"id"_L1, obj.value("id"_L1)}, {"error"_L1, error}});
        }
    }));
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    initialize(manager);
    const QSignalSpy receivedSpy(&manager, &McpProtocolClientProtocolManager::received);
    const qint64 identifier = manager.executeAction(McpProtocolClientProtocolManager::MethodType::ListTools);
    QTRY_COMPARE(receivedSpy.count(), 1);
    const QJsonObject response = receivedSpy.at(0).at(0).toJsonObject();
    QCOMPARE(response.value("id"_L1).toInteger(), identifier);
    QCOMPARE(response.value("error"_L1).toObject().value("code"_L1).toInt(), -32602);
}

void McpProtocolClientProtocolManagerTest::shouldEmitListChangedSignals()
{
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler(u"2025-11-25"_s, [](const QJsonObject &obj, QTcpSocket *socket) {
        // Server sends notifications in stream before response
        QByteArray events;
        for (const auto &method : {u"notifications/tools/list_changed"_s, u"notifications/prompts/list_changed"_s, u"notifications/resources/list_changed"_s}) {
            events += FakeMcpHttpServer::jsonEvent(QJsonObject{{"jsonrpc"_L1, u"2.0"_s}, {"method"_L1, method}});
        }
        FakeMcpHttpServer::sendEventStream(socket, events + FakeMcpHttpServer::jsonEvent(result(obj.value("id"_L1))));
    }));
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    initialize(manager);
    const QSignalSpy toolsSpy(&manager, &McpProtocolClientProtocolManager::toolsListChanged);
    const QSignalSpy promptsSpy(&manager, &McpProtocolClientProtocolManager::promptsListChanged);
    const QSignalSpy resourcesSpy(&manager, &McpProtocolClientProtocolManager::resourcesListChanged);
    const QSignalSpy receivedSpy(&manager, &McpProtocolClientProtocolManager::received);
    manager.executeAction(McpProtocolClientProtocolManager::MethodType::Ping);
    QTRY_COMPARE(receivedSpy.count(), 4);
    QCOMPARE(toolsSpy.count(), 1);
    QCOMPARE(promptsSpy.count(), 1);
    QCOMPARE(resourcesSpy.count(), 1);
    // Notifications are still emitted with received()
    QCOMPARE(receivedSpy.at(0).at(1).value<McpProtocolClientProtocolManager::MethodType>(), McpProtocolClientProtocolManager::MethodType::ServerNotification);
}

#include "moc_mcpprotocolclientprotocolmanagertest.cpp"
