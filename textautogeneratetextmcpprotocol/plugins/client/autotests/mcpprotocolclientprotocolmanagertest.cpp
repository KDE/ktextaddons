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
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCompleteRequestParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCompleteResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCreateMessageRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCreateMessageResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitRequestURLParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolGetPromptResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolLoggingMessageNotificationParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolProgressNotificationParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPromptReference>
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

FakeMcpHttpServer::Handler createElicitationHandler()
{
    return createHandler(u"2025-11-25"_s, [](const QJsonObject &obj, QTcpSocket *socket) {
        // Server asks for user input before response
        const QJsonObject elicit{{"jsonrpc"_L1, u"2.0"_s},
                                 {"id"_L1, u"srv-1"_s},
                                 {"method"_L1, u"elicitation/create"_s},
                                 {"params"_L1,
                                  QJsonObject{{"mode"_L1, u"form"_s},
                                              {"message"_L1, u"Name?"_s},
                                              {"requestedSchema"_L1, QJsonObject{{"type"_L1, u"object"_s}, {"properties"_L1, QJsonObject{}}}}}}};
        FakeMcpHttpServer::sendEventStream(socket, FakeMcpHttpServer::jsonEvent(elicit) + FakeMcpHttpServer::jsonEvent(result(obj.value("id"_L1))));
    });
}

FakeMcpHttpServer::Handler createUrlElicitationHandler()
{
    return createHandler(u"2025-11-25"_s, [](const QJsonObject &obj, QTcpSocket *socket) {
        // Server asks user to open an URL, then informs that interaction is completed
        const QJsonObject elicit{{"jsonrpc"_L1, u"2.0"_s},
                                 {"id"_L1, u"srv-1"_s},
                                 {"method"_L1, u"elicitation/create"_s},
                                 {"params"_L1,
                                  QJsonObject{{"mode"_L1, u"url"_s},
                                              {"elicitationId"_L1, u"elicit-1"_s},
                                              {"message"_L1, u"Please authorize"_s},
                                              {"url"_L1, u"https://example.com/authorize"_s}}}};
        const QJsonObject complete{{"jsonrpc"_L1, u"2.0"_s},
                                   {"method"_L1, u"notifications/elicitation/complete"_s},
                                   {"params"_L1, QJsonObject{{"elicitationId"_L1, u"elicit-1"_s}}}};
        FakeMcpHttpServer::sendEventStream(socket,
                                           FakeMcpHttpServer::jsonEvent(elicit) + FakeMcpHttpServer::jsonEvent(complete)
                                               + FakeMcpHttpServer::jsonEvent(result(obj.value("id"_L1))));
    });
}

FakeMcpHttpServer::Handler createSamplingHandler()
{
    return createHandler(u"2025-11-25"_s, [](const QJsonObject &obj, QTcpSocket *socket) {
        // Server asks for a LLM generation before response
        const QJsonObject message{{"role"_L1, u"user"_s}, {"content"_L1, QJsonObject{{"type"_L1, u"text"_s}, {"text"_L1, u"Hello"_s}}}};
        const QJsonObject sampling{{"jsonrpc"_L1, u"2.0"_s},
                                   {"id"_L1, u"srv-1"_s},
                                   {"method"_L1, u"sampling/createMessage"_s},
                                   {"params"_L1, QJsonObject{{"messages"_L1, QJsonArray{message}}, {"maxTokens"_L1, 100}}}};
        FakeMcpHttpServer::sendEventStream(socket, FakeMcpHttpServer::jsonEvent(sampling) + FakeMcpHttpServer::jsonEvent(result(obj.value("id"_L1))));
    });
}

// Response of client to server request "srv-1"
QJsonObject serverRequestResponse(const FakeMcpHttpServer &server)
{
    for (const auto &request : server.requests("POST")) {
        const QJsonObject obj = request.json();
        if (!obj.contains("method"_L1) && obj.value("id"_L1).toString() == u"srv-1"_s) {
            return obj;
        }
    }
    return {};
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

void McpProtocolClientProtocolManagerTest::shouldAnswerElicitationRequest()
{
    {
        // Declined automatically without receiver
        FakeMcpHttpServer fakeServer;
        fakeServer.setHandler(createElicitationHandler());
        McpProtocolClientProtocolManager manager(createServer(fakeServer));
        manager.setElicitationSupported(true);
        initialize(manager);
        manager.executeAction(McpProtocolClientProtocolManager::MethodType::ListTools);
        QTRY_VERIFY(!serverRequestResponse(fakeServer).isEmpty());
        QCOMPARE(serverRequestResponse(fakeServer).value("result"_L1).toObject().value("action"_L1).toString(), u"decline"_s);
    }
    {
        // Answered by receiver
        FakeMcpHttpServer fakeServer;
        fakeServer.setHandler(createElicitationHandler());
        McpProtocolClientProtocolManager manager(createServer(fakeServer));
        manager.setElicitationSupported(true);
        int requested = 0;
        connect(&manager,
                &McpProtocolClientProtocolManager::elicitationRequested,
                this,
                [&manager, &requested](const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::RequestId &id,
                                       const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequest &request) {
                    Q_UNUSED(request)
                    ++requested;
                    QCOMPARE(std::get<QString>(id), u"srv-1"_s);
                    TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult result;
                    result.setAction(TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult::Action::Accept);
                    manager.respondToElicitation(id, result);
                });
        initialize(manager);
        manager.executeAction(McpProtocolClientProtocolManager::MethodType::ListTools);
        QTRY_VERIFY(!serverRequestResponse(fakeServer).isEmpty());
        QCOMPARE(requested, 1);
        QCOMPARE(serverRequestResponse(fakeServer).value("result"_L1).toObject().value("action"_L1).toString(), u"accept"_s);
    }
}

void McpProtocolClientProtocolManagerTest::shouldRejectDuplicatedElicitationId()
{
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler(u"2025-11-25"_s, [](const QJsonObject &obj, QTcpSocket *socket) {
        // Server sends twice the same request id
        const QJsonObject elicit{{"jsonrpc"_L1, u"2.0"_s},
                                 {"id"_L1, u"srv-1"_s},
                                 {"method"_L1, u"elicitation/create"_s},
                                 {"params"_L1,
                                  QJsonObject{{"mode"_L1, u"form"_s},
                                              {"message"_L1, u"Name?"_s},
                                              {"requestedSchema"_L1, QJsonObject{{"type"_L1, u"object"_s}, {"properties"_L1, QJsonObject{}}}}}}};
        FakeMcpHttpServer::sendEventStream(socket,
                                           FakeMcpHttpServer::jsonEvent(elicit) + FakeMcpHttpServer::jsonEvent(elicit)
                                               + FakeMcpHttpServer::jsonEvent(result(obj.value("id"_L1))));
    }));
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    manager.setElicitationSupported(true);
    // User doesn't answer: first request stays pending
    const QSignalSpy elicitationSpy(&manager, &McpProtocolClientProtocolManager::elicitationRequested);
    initialize(manager);
    manager.executeAction(McpProtocolClientProtocolManager::MethodType::ListTools);
    QTRY_VERIFY(!serverRequestResponse(fakeServer).isEmpty());
    QCOMPARE(serverRequestResponse(fakeServer).value("error"_L1).toObject().value("code"_L1).toInt(), -32600);
    QCOMPARE(elicitationSpy.count(), 1);
}

void McpProtocolClientProtocolManagerTest::shouldAnnounceUrlElicitationCapability()
{
    {
        FakeMcpHttpServer fakeServer;
        fakeServer.setHandler(createHandler());
        McpProtocolClientProtocolManager manager(createServer(fakeServer));
        QVERIFY(!manager.urlElicitationSupported());
        manager.setUrlElicitationSupported(true);
        QVERIFY(manager.urlElicitationSupported());
        initialize(manager);
        const QJsonObject initialize = postedMessages(fakeServer, u"initialize"_s).constFirst();
        const QJsonObject capabilities = initialize.value("params"_L1).toObject().value("capabilities"_L1).toObject();
        QCOMPARE(capabilities.value("elicitation"_L1).toObject(), QJsonObject({{"url"_L1, QJsonObject()}}));
    }
    {
        FakeMcpHttpServer fakeServer;
        fakeServer.setHandler(createHandler());
        McpProtocolClientProtocolManager manager(createServer(fakeServer));
        manager.setElicitationSupported(true);
        manager.setUrlElicitationSupported(true);
        initialize(manager);
        const QJsonObject initialize = postedMessages(fakeServer, u"initialize"_s).constFirst();
        const QJsonObject capabilities = initialize.value("params"_L1).toObject().value("capabilities"_L1).toObject();
        QCOMPARE(capabilities.value("elicitation"_L1).toObject(), QJsonObject({{"form"_L1, QJsonObject()}, {"url"_L1, QJsonObject()}}));
    }
}

void McpProtocolClientProtocolManagerTest::shouldAnswerUrlElicitationRequest()
{
    {
        // Url mode not announced: request is rejected
        FakeMcpHttpServer fakeServer;
        fakeServer.setHandler(createUrlElicitationHandler());
        McpProtocolClientProtocolManager manager(createServer(fakeServer));
        manager.setElicitationSupported(true);
        const QSignalSpy elicitationSpy(&manager, &McpProtocolClientProtocolManager::elicitationRequested);
        const QSignalSpy completedSpy(&manager, &McpProtocolClientProtocolManager::elicitationCompleted);
        initialize(manager);
        manager.executeAction(McpProtocolClientProtocolManager::MethodType::ListTools);
        QTRY_VERIFY(!serverRequestResponse(fakeServer).isEmpty());
        QCOMPARE(serverRequestResponse(fakeServer).value("error"_L1).toObject().value("code"_L1).toInt(), -32602);
        QCOMPARE(elicitationSpy.count(), 0);
        QCOMPARE(completedSpy.count(), 0);
    }
    {
        FakeMcpHttpServer fakeServer;
        fakeServer.setHandler(createUrlElicitationHandler());
        McpProtocolClientProtocolManager manager(createServer(fakeServer));
        manager.setUrlElicitationSupported(true);
        connect(&manager,
                &McpProtocolClientProtocolManager::elicitationRequested,
                this,
                [&manager](const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::RequestId &id,
                           const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequest &request) {
                    const auto params = request.params();
                    const auto urlParams = std::get_if<TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams>(&params);
                    QVERIFY(urlParams);
                    QCOMPARE(urlParams->url(), u"https://example.com/authorize"_s);
                    QCOMPARE(urlParams->elicitationId(), u"elicit-1"_s);
                    TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult result;
                    result.setAction(TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult::Action::Accept);
                    manager.respondToElicitation(id, result);
                });
        const QSignalSpy completedSpy(&manager, &McpProtocolClientProtocolManager::elicitationCompleted);
        initialize(manager);
        manager.executeAction(McpProtocolClientProtocolManager::MethodType::ListTools);
        QTRY_VERIFY(!serverRequestResponse(fakeServer).isEmpty());
        QCOMPARE(serverRequestResponse(fakeServer).value("result"_L1).toObject().value("action"_L1).toString(), u"accept"_s);
        QTRY_COMPARE(completedSpy.count(), 1);
        QCOMPARE(completedSpy.at(0).at(0).toString(), u"elicit-1"_s);
    }
}

void McpProtocolClientProtocolManagerTest::shouldAnnounceRootsCapability()
{
    {
        // Not announced by default
        FakeMcpHttpServer fakeServer;
        fakeServer.setHandler(createHandler());
        McpProtocolClientProtocolManager manager(createServer(fakeServer));
        QVERIFY(!manager.rootsSupported());
        initialize(manager);
        const QJsonObject initialize = postedMessages(fakeServer, u"initialize"_s).constFirst();
        QVERIFY(!initialize.value("params"_L1).toObject().value("capabilities"_L1).toObject().contains("roots"_L1));
    }
    {
        FakeMcpHttpServer fakeServer;
        fakeServer.setHandler(createHandler());
        McpProtocolClientProtocolManager manager(createServer(fakeServer));
        manager.setRootsSupported(true);
        QVERIFY(manager.rootsSupported());
        initialize(manager);
        const QJsonObject initialize = postedMessages(fakeServer, u"initialize"_s).constFirst();
        const QJsonObject capabilities = initialize.value("params"_L1).toObject().value("capabilities"_L1).toObject();
        QCOMPARE(capabilities.value("roots"_L1).toObject(), QJsonObject({{"listChanged"_L1, true}}));
    }
}

void McpProtocolClientProtocolManagerTest::shouldAnswerRootsList()
{
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler(u"2025-11-25"_s, [](const QJsonObject &obj, QTcpSocket *socket) {
        const QJsonObject roots{{"jsonrpc"_L1, u"2.0"_s}, {"id"_L1, u"srv-1"_s}, {"method"_L1, u"roots/list"_s}};
        FakeMcpHttpServer::sendEventStream(socket, FakeMcpHttpServer::jsonEvent(roots) + FakeMcpHttpServer::jsonEvent(result(obj.value("id"_L1))));
    }));
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    manager.setRootsSupported(true);
    TextAutoGenerateTextMcpProtocolCore::McpProtocolRoot root;
    root.setUri(u"file:///home/user/project"_s);
    root.setName(u"project"_s);
    manager.setRoots({root});
    initialize(manager);
    manager.executeAction(McpProtocolClientProtocolManager::MethodType::ListTools);
    QTRY_VERIFY(!serverRequestResponse(fakeServer).isEmpty());
    const QJsonArray roots = serverRequestResponse(fakeServer).value("result"_L1).toObject().value("roots"_L1).toArray();
    QCOMPARE(roots.count(), 1);
    QCOMPARE(roots.at(0).toObject().value("uri"_L1).toString(), u"file:///home/user/project"_s);
    QCOMPARE(roots.at(0).toObject().value("name"_L1).toString(), u"project"_s);
}

void McpProtocolClientProtocolManagerTest::shouldNotifyRootsListChanged()
{
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler());
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    manager.setRootsSupported(true);
    TextAutoGenerateTextMcpProtocolCore::McpProtocolRoot root;
    root.setUri(u"file:///home/user/project"_s);
    // Not initialized: nothing is sent
    manager.setRoots({root});
    QCOMPARE(manager.roots().count(), 1);
    initialize(manager);
    QTRY_COMPARE(postedMessages(fakeServer, u"notifications/initialized"_s).count(), 1);
    QCOMPARE(postedMessages(fakeServer, u"notifications/roots/list_changed"_s).count(), 0);
    root.setUri(u"file:///home/user/other"_s);
    manager.setRoots({root});
    QTRY_COMPARE(postedMessages(fakeServer, u"notifications/roots/list_changed"_s).count(), 1);
    // Same list: nothing is sent
    manager.setRoots({root});
    manager.setRoots({});
    QTRY_COMPARE(postedMessages(fakeServer, u"notifications/roots/list_changed"_s).count(), 2);
}

void McpProtocolClientProtocolManagerTest::shouldAnnounceSamplingCapability()
{
    {
        // Not announced by default
        FakeMcpHttpServer fakeServer;
        fakeServer.setHandler(createHandler());
        McpProtocolClientProtocolManager manager(createServer(fakeServer));
        QVERIFY(!manager.samplingSupported());
        initialize(manager);
        const QJsonObject initialize = postedMessages(fakeServer, u"initialize"_s).constFirst();
        QVERIFY(!initialize.value("params"_L1).toObject().value("capabilities"_L1).toObject().contains("sampling"_L1));
    }
    {
        FakeMcpHttpServer fakeServer;
        fakeServer.setHandler(createHandler());
        McpProtocolClientProtocolManager manager(createServer(fakeServer));
        manager.setSamplingSupported(true);
        QVERIFY(manager.samplingSupported());
        initialize(manager);
        const QJsonObject initialize = postedMessages(fakeServer, u"initialize"_s).constFirst();
        const QJsonObject capabilities = initialize.value("params"_L1).toObject().value("capabilities"_L1).toObject();
        QCOMPARE(capabilities.value("sampling"_L1).toObject(), QJsonObject());
        QVERIFY(capabilities.contains("sampling"_L1));
    }
}

void McpProtocolClientProtocolManagerTest::shouldAnswerSamplingRequest()
{
    {
        // Not supported: method not found
        FakeMcpHttpServer fakeServer;
        fakeServer.setHandler(createSamplingHandler());
        McpProtocolClientProtocolManager manager(createServer(fakeServer));
        initialize(manager);
        manager.executeAction(McpProtocolClientProtocolManager::MethodType::ListTools);
        QTRY_VERIFY(!serverRequestResponse(fakeServer).isEmpty());
        QCOMPARE(serverRequestResponse(fakeServer).value("error"_L1).toObject().value("code"_L1).toInt(), -32601);
    }
    {
        // Rejected automatically without receiver
        FakeMcpHttpServer fakeServer;
        fakeServer.setHandler(createSamplingHandler());
        McpProtocolClientProtocolManager manager(createServer(fakeServer));
        manager.setSamplingSupported(true);
        initialize(manager);
        manager.executeAction(McpProtocolClientProtocolManager::MethodType::ListTools);
        QTRY_VERIFY(!serverRequestResponse(fakeServer).isEmpty());
        QCOMPARE(serverRequestResponse(fakeServer).value("error"_L1).toObject().value("code"_L1).toInt(), -1);
    }
    {
        // Rejected by receiver
        FakeMcpHttpServer fakeServer;
        fakeServer.setHandler(createSamplingHandler());
        McpProtocolClientProtocolManager manager(createServer(fakeServer));
        manager.setSamplingSupported(true);
        connect(&manager,
                &McpProtocolClientProtocolManager::samplingRequested,
                this,
                [&manager](const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::RequestId &id,
                           const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequest &request) {
                    Q_UNUSED(request)
                    manager.rejectSampling(id, u"No"_s);
                });
        initialize(manager);
        manager.executeAction(McpProtocolClientProtocolManager::MethodType::ListTools);
        QTRY_VERIFY(!serverRequestResponse(fakeServer).isEmpty());
        const QJsonObject error = serverRequestResponse(fakeServer).value("error"_L1).toObject();
        QCOMPARE(error.value("code"_L1).toInt(), -1);
        QCOMPARE(error.value("message"_L1).toString(), u"No"_s);
    }
    {
        // Answered by receiver
        FakeMcpHttpServer fakeServer;
        fakeServer.setHandler(createSamplingHandler());
        McpProtocolClientProtocolManager manager(createServer(fakeServer));
        manager.setSamplingSupported(true);
        int requested = 0;
        connect(&manager,
                &McpProtocolClientProtocolManager::samplingRequested,
                this,
                [&manager, &requested](const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::RequestId &id,
                                       const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequest &request) {
                    ++requested;
                    QCOMPARE(std::get<QString>(id), u"srv-1"_s);
                    QCOMPARE(request.params().maxTokens(), 100);
                    QCOMPARE(request.params().messages().count(), 1);
                    TextAutoGenerateTextMcpProtocolCore::McpProtocolTextContent content;
                    content.setText(u"Hi"_s);
                    TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageResult result;
                    result.setContent(content);
                    result.setModel(u"model"_s);
                    result.setRole(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::Role::Assistant);
                    manager.respondToSampling(id, result);
                });
        initialize(manager);
        manager.executeAction(McpProtocolClientProtocolManager::MethodType::ListTools);
        QTRY_VERIFY(!serverRequestResponse(fakeServer).isEmpty());
        QCOMPARE(requested, 1);
        const QJsonObject result = serverRequestResponse(fakeServer).value("result"_L1).toObject();
        QCOMPARE(result.value("model"_L1).toString(), u"model"_s);
        QCOMPARE(result.value("role"_L1).toString(), u"assistant"_s);
        QCOMPARE(result.value("content"_L1).toObject().value("text"_L1).toString(), u"Hi"_s);
    }
}

void McpProtocolClientProtocolManagerTest::shouldAcceptOlderProtocolVersion_data()
{
    QTest::addColumn<QString>("protocolVersion");
    QTest::newRow("2024-11-05") << u"2024-11-05"_s;
    QTest::newRow("2025-03-26") << u"2025-03-26"_s;
    QTest::newRow("2025-06-18") << u"2025-06-18"_s;
}

void McpProtocolClientProtocolManagerTest::shouldAcceptOlderProtocolVersion()
{
    QFETCH(QString, protocolVersion);
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler(protocolVersion));
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    const QSignalSpy errorSpy(&manager, &McpProtocolClientProtocolManager::error);
    initialize(manager);
    QCOMPARE(errorSpy.count(), 0);
    QCOMPARE(manager.initializeResult().protocolVersion(), protocolVersion);

    // Version chosen by server is sent in next requests
    const QSignalSpy receivedSpy(&manager, &McpProtocolClientProtocolManager::received);
    QVERIFY(manager.executeAction(McpProtocolClientProtocolManager::MethodType::ListTools) > 0);
    QTRY_COMPARE(receivedSpy.count(), 1);
    for (const auto &request : fakeServer.requests("POST")) {
        if (request.json().value("method"_L1).toString() == u"tools/list"_s) {
            QCOMPARE(request.header("MCP-Protocol-Version"), protocolVersion.toLatin1());
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

void McpProtocolClientProtocolManagerTest::shouldNotTimeoutWhileElicitationIsPending()
{
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler(u"2025-11-25"_s, [](const QJsonObject &, QTcpSocket *socket) {
        // Ask for user input, never answer request
        const QJsonObject elicit{{"jsonrpc"_L1, u"2.0"_s},
                                 {"id"_L1, u"srv-1"_s},
                                 {"method"_L1, u"elicitation/create"_s},
                                 {"params"_L1,
                                  QJsonObject{{"mode"_L1, u"form"_s},
                                              {"message"_L1, u"Name?"_s},
                                              {"requestedSchema"_L1, QJsonObject{{"type"_L1, u"object"_s}, {"properties"_L1, QJsonObject{}}}}}}};
        FakeMcpHttpServer::sendEventStream(socket, FakeMcpHttpServer::jsonEvent(elicit), false);
    }));
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    manager.setElicitationSupported(true);
    manager.setRequestTimeout(std::chrono::milliseconds(200));
    std::optional<TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::RequestId> elicitationId;
    connect(&manager,
            &McpProtocolClientProtocolManager::elicitationRequested,
            this,
            [&elicitationId](const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::RequestId &id,
                             const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequest &request) {
                Q_UNUSED(request)
                elicitationId = id;
            });
    initialize(manager);
    QList<QJsonObject> responses;
    connect(&manager,
            &McpProtocolClientProtocolManager::received,
            this,
            [&responses](const QJsonObject &obj, McpProtocolClientProtocolManager::MethodType type) {
                if (type == McpProtocolClientProtocolManager::MethodType::ListTools) {
                    responses.append(obj);
                }
            });
    manager.executeAction(McpProtocolClientProtocolManager::MethodType::ListTools);
    QTRY_VERIFY(elicitationId.has_value());
    // User takes time to answer: request doesn't time out
    QTest::qWait(600);
    QVERIFY(responses.isEmpty());
    QVERIFY(postedMessages(fakeServer, u"notifications/cancelled"_s).isEmpty());

    TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult result;
    result.setAction(TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult::Action::Cancel);
    manager.respondToElicitation(*elicitationId, result);
    QTRY_VERIFY(!serverRequestResponse(fakeServer).isEmpty());
    // Timeout restarts when user answered
    QTRY_COMPARE(responses.count(), 1);
    QCOMPARE(responses.constFirst().value("error"_L1).toObject().value("code"_L1).toInt(), -32001);
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
    // Requests are refused when client is stopped
    QCOMPARE(manager.executeAction(McpProtocolClientProtocolManager::MethodType::Ping), -1);
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

void McpProtocolClientProtocolManagerTest::shouldFetchPageWithEmptyCursor()
{
    // Empty string is a valid opaque cursor: only absence of nextCursor ends pagination
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler(u"2025-11-25"_s, [](const QJsonObject &obj, QTcpSocket *socket) {
        const QJsonObject params = obj.value("params"_L1).toObject();
        QJsonObject page;
        if (!params.contains("cursor"_L1)) {
            page = QJsonObject{{"tools"_L1, QJsonArray{tool(u"a"_s)}}, {"nextCursor"_L1, QString()}};
        } else {
            page = QJsonObject{{"tools"_L1, QJsonArray{tool(u"b"_s)}}};
        }
        sendJson(socket, result(obj.value("id"_L1), page));
    }));
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    initialize(manager);
    const QSignalSpy receivedSpy(&manager, &McpProtocolClientProtocolManager::received);
    manager.executeAction(McpProtocolClientProtocolManager::MethodType::ListTools);
    QTRY_COMPARE(receivedSpy.count(), 1);
    QCOMPARE(toolNames(receivedSpy.at(0).at(0).toJsonObject()), QStringList({u"a"_s, u"b"_s}));
    const auto requests = postedMessages(fakeServer, u"tools/list"_s);
    QCOMPARE(requests.count(), 2);
    QVERIFY(requests.at(1).value("params"_L1).toObject().contains("cursor"_L1));
    QCOMPARE(requests.at(1).value("params"_L1).toObject().value("cursor"_L1).toString(), QString());
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

void McpProtocolClientProtocolManagerTest::shouldLogMessages()
{
    using MessageInfo = McpProtocolClientProtocolManager::MessageInfo;
    using MessageDirection = McpProtocolClientProtocolManager::MessageDirection;
    using MethodType = McpProtocolClientProtocolManager::MethodType;
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler());
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    QList<MessageInfo> infos;
    connect(&manager, &McpProtocolClientProtocolManager::messageLogged, this, [&infos](const MessageInfo &info) {
        infos.append(info);
    });
    initialize(manager);
    QCOMPARE(infos.count(), 2);
    QCOMPARE(infos.at(0).direction, MessageDirection::Sent);
    QCOMPARE(infos.at(0).type, MethodType::Initialize);
    QCOMPARE(infos.at(0).message.value("method"_L1).toString(), u"initialize"_s);
    QVERIFY(infos.at(0).dateTime.isValid());
    QCOMPARE(infos.at(0).elapsedMs, -1);
    QCOMPARE(infos.at(1).direction, MessageDirection::Received);
    QCOMPARE(infos.at(1).type, MethodType::Initialize);
    QCOMPARE(infos.at(1).identifier, infos.at(0).identifier);
    QVERIFY(infos.at(1).elapsedMs >= 0);

    infos.clear();
    const qint64 identifier = manager.executeAction(MethodType::ListTools);
    QTRY_COMPARE(infos.count(), 2);
    QCOMPARE(infos.at(0).direction, MessageDirection::Sent);
    QCOMPARE(infos.at(0).identifier, identifier);
    QCOMPARE(infos.at(0).type, MethodType::ListTools);
    QCOMPARE(infos.at(1).direction, MessageDirection::Received);
    QCOMPARE(infos.at(1).identifier, identifier);
    QCOMPARE(infos.at(1).type, MethodType::ListTools);
    QVERIFY(infos.at(1).message.contains("result"_L1));
}

void McpProtocolClientProtocolManagerTest::shouldSubscribeResource()
{
    using MethodType = McpProtocolClientProtocolManager::MethodType;
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler(
        u"2025-11-25"_s,
        [](const QJsonObject &obj, QTcpSocket *socket) {
            // Server informs that subscribed resource changed before response
            const QJsonObject updated{{"jsonrpc"_L1, u"2.0"_s},
                                      {"method"_L1, u"notifications/resources/updated"_s},
                                      {"params"_L1, QJsonObject{{"uri"_L1, obj.value("params"_L1).toObject().value("uri"_L1)}}}};
            FakeMcpHttpServer::sendEventStream(socket, FakeMcpHttpServer::jsonEvent(updated) + FakeMcpHttpServer::jsonEvent(result(obj.value("id"_L1))));
        },
        QJsonObject{{"resources"_L1, QJsonObject{{"subscribe"_L1, true}}}}));
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    // Not initialized
    QCOMPARE(manager.subscribeResource(u"file:///foo.txt"_s), -1);
    initialize(manager);
    QCOMPARE(manager.subscribeResource(QString()), -1);
    // Use subscribeResource()
    QCOMPARE(manager.executeAction(MethodType::SubscribeResource), -1);

    const QSignalSpy updatedSpy(&manager, &McpProtocolClientProtocolManager::resourceUpdated);
    const QSignalSpy receivedSpy(&manager, &McpProtocolClientProtocolManager::received);
    const qint64 identifier = manager.subscribeResource(u"file:///foo.txt"_s);
    QVERIFY(identifier > 0);
    QTRY_COMPARE(receivedSpy.count(), 2);
    QCOMPARE(updatedSpy.count(), 1);
    QCOMPARE(updatedSpy.at(0).at(0).toString(), u"file:///foo.txt"_s);
    QCOMPARE(receivedSpy.at(1).at(1).value<MethodType>(), MethodType::SubscribeResource);
    QCOMPARE(receivedSpy.at(1).at(0).toJsonObject().value("id"_L1).toInteger(), identifier);
    QCOMPARE(postedMessages(fakeServer, u"resources/subscribe"_s).constFirst().value("params"_L1).toObject().value("uri"_L1).toString(), u"file:///foo.txt"_s);

    const qint64 unsubscribeIdentifier = manager.unsubscribeResource(u"file:///foo.txt"_s);
    QVERIFY(unsubscribeIdentifier > 0);
    QTRY_COMPARE(receivedSpy.count(), 4);
    QCOMPARE(receivedSpy.at(3).at(1).value<MethodType>(), MethodType::UnsubscribeResource);
    QCOMPARE(postedMessages(fakeServer, u"resources/unsubscribe"_s).count(), 1);
}

void McpProtocolClientProtocolManagerTest::shouldNotSubscribeWhenServerDoesNotSupportSubscription()
{
    FakeMcpHttpServer fakeServer;
    // Resources without "subscribe"
    fakeServer.setHandler(createHandler(
        u"2025-11-25"_s,
        [](const QJsonObject &obj, QTcpSocket *socket) {
            sendJson(socket, result(obj.value("id"_L1)));
        },
        QJsonObject{{"resources"_L1, QJsonObject{}}}));
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    initialize(manager);
    QCOMPARE(manager.subscribeResource(u"file:///foo.txt"_s), -1);
    QCOMPARE(manager.unsubscribeResource(u"file:///foo.txt"_s), -1);
    QTest::qWait(100);
    QVERIFY(postedMessages(fakeServer, u"resources/subscribe"_s).isEmpty());
}

void McpProtocolClientProtocolManagerTest::shouldEmitLoggingMessage()
{
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler(u"2025-11-25"_s, [](const QJsonObject &obj, QTcpSocket *socket) {
        const QJsonObject log{{"jsonrpc"_L1, u"2.0"_s},
                              {"method"_L1, u"notifications/message"_s},
                              {"params"_L1, QJsonObject{{"level"_L1, u"warning"_s}, {"logger"_L1, u"db"_s}, {"data"_L1, u"Slow query"_s}}}};
        FakeMcpHttpServer::sendEventStream(socket, FakeMcpHttpServer::jsonEvent(log) + FakeMcpHttpServer::jsonEvent(result(obj.value("id"_L1))));
    }));
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    initialize(manager);
    QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolLoggingMessageNotificationParams> logs;
    connect(&manager,
            &McpProtocolClientProtocolManager::loggingMessageReceived,
            this,
            [&logs](const TextAutoGenerateTextMcpProtocolCore::McpProtocolLoggingMessageNotificationParams &params) {
                logs.append(params);
            });
    manager.executeAction(McpProtocolClientProtocolManager::MethodType::Ping);
    QTRY_COMPARE(logs.count(), 1);
    QCOMPARE(logs.at(0).level(), TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel::Warning);
    QCOMPARE(logs.at(0).logger(), u"db"_s);
    QCOMPARE(logs.at(0).data().toString(), u"Slow query"_s);
}

void McpProtocolClientProtocolManagerTest::shouldEmitProgress()
{
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler(u"2025-11-25"_s, [](const QJsonObject &obj, QTcpSocket *socket) {
        // Server reports progress with token sent by client, then an unknown token
        const QJsonValue token = obj.value("params"_L1).toObject().value("_meta"_L1).toObject().value("progressToken"_L1);
        const auto progress = [](const QJsonValue &progressToken, double value) {
            return QJsonObject{{"jsonrpc"_L1, u"2.0"_s},
                               {"method"_L1, u"notifications/progress"_s},
                               {"params"_L1, QJsonObject{{"progressToken"_L1, progressToken}, {"progress"_L1, value}, {"total"_L1, 2}}}};
        };
        FakeMcpHttpServer::sendEventStream(socket,
                                           FakeMcpHttpServer::jsonEvent(progress(token, 1)) + FakeMcpHttpServer::jsonEvent(progress(u"unknown"_s, 1))
                                               + FakeMcpHttpServer::jsonEvent(progress(token, 2))
                                               + FakeMcpHttpServer::jsonEvent(result(obj.value("id"_L1), QJsonObject{{"content"_L1, QJsonArray{}}})));
    }));
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    initialize(manager);
    const QSignalSpy progressSpy(&manager, &McpProtocolClientProtocolManager::progressReceived);
    const QSignalSpy receivedSpy(&manager, &McpProtocolClientProtocolManager::received);
    const qint64 identifier = manager.callTool(u"weather"_s);
    QVERIFY(identifier > 0);
    QTRY_COMPARE(receivedSpy.count(), 4);
    QCOMPARE(progressSpy.count(), 2);
    QCOMPARE(progressSpy.at(0).at(0).toLongLong(), identifier);
    QCOMPARE(progressSpy.at(1).at(0).toLongLong(), identifier);

    const QJsonObject request = postedMessages(fakeServer, u"tools/call"_s).constFirst();
    QCOMPARE(request.value("params"_L1).toObject().value("_meta"_L1).toObject().value("progressToken"_L1).toInteger(), identifier);
}

void McpProtocolClientProtocolManagerTest::shouldComplete()
{
    using MethodType = McpProtocolClientProtocolManager::MethodType;
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler(
        u"2025-11-25"_s,
        [](const QJsonObject &obj, QTcpSocket *socket) {
            const QString value = obj.value("params"_L1).toObject().value("argument"_L1).toObject().value("value"_L1).toString();
            const QJsonObject completion{{"values"_L1, QJsonArray{QString(value + u"thon"_s), QString(value + u"tch"_s)}}, {"hasMore"_L1, false}};
            sendJson(socket, result(obj.value("id"_L1), QJsonObject{{"completion"_L1, completion}}));
        },
        QJsonObject{{"prompts"_L1, QJsonObject{}}, {"completions"_L1, QJsonObject{}}}));
    McpProtocolClientProtocolManager manager(createServer(fakeServer));

    TextAutoGenerateTextMcpProtocolCore::McpProtocolPromptReference ref;
    ref.setName(u"review"_s);
    TextAutoGenerateTextMcpProtocolCore::McpProtocolCompleteRequestParams::Argument argument;
    argument.setName(u"language"_s);
    argument.setValue(u"py"_s);
    TextAutoGenerateTextMcpProtocolCore::McpProtocolCompleteRequestParams params;
    params.setRef(ref);
    params.setArgument(argument);
    // Not initialized
    QCOMPARE(manager.complete(params), -1);
    initialize(manager);
    QCOMPARE(manager.complete({}), -1);
    QCOMPARE(manager.executeAction(MethodType::Complete), -1);

    const QSignalSpy receivedSpy(&manager, &McpProtocolClientProtocolManager::received);
    const qint64 identifier = manager.complete(params);
    QVERIFY(identifier > 0);
    QTRY_COMPARE(receivedSpy.count(), 1);
    QCOMPARE(receivedSpy.at(0).at(1).value<MethodType>(), MethodType::Complete);
    const QJsonObject response = receivedSpy.at(0).at(0).toJsonObject();
    QCOMPARE(response.value("id"_L1).toInteger(), identifier);
    const auto completeResult = TextAutoGenerateTextMcpProtocolCore::McpProtocolCompleteResult::fromJson(response.value("result"_L1).toObject());
    QCOMPARE(completeResult.completion().values(), (QStringList{u"python"_s, u"pytch"_s}));

    const QJsonObject requestParams = postedMessages(fakeServer, u"completion/complete"_s).constFirst().value("params"_L1).toObject();
    QCOMPARE(requestParams.value("ref"_L1).toObject(), (QJsonObject{{"type"_L1, u"ref/prompt"_s}, {"name"_L1, u"review"_s}}));
    QCOMPARE(requestParams.value("argument"_L1).toObject(), (QJsonObject{{"name"_L1, u"language"_s}, {"value"_L1, u"py"_s}}));
}

void McpProtocolClientProtocolManagerTest::shouldSetLoggingLevel()
{
    using MethodType = McpProtocolClientProtocolManager::MethodType;
    using LoggingLevel = TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel;
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler(
        u"2025-11-25"_s,
        [](const QJsonObject &obj, QTcpSocket *socket) {
            sendJson(socket, result(obj.value("id"_L1)));
        },
        QJsonObject{{"logging"_L1, QJsonObject{}}}));
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    // Not initialized
    QCOMPARE(manager.setLoggingLevel(LoggingLevel::Info), -1);
    initialize(manager);
    QCOMPARE(manager.setLoggingLevel(LoggingLevel::Unknown), -1);
    QCOMPARE(manager.executeAction(MethodType::SetLoggingLevel), -1);

    const QSignalSpy receivedSpy(&manager, &McpProtocolClientProtocolManager::received);
    const qint64 identifier = manager.setLoggingLevel(LoggingLevel::Warning);
    QVERIFY(identifier > 0);
    QTRY_COMPARE(receivedSpy.count(), 1);
    QCOMPARE(receivedSpy.at(0).at(1).value<MethodType>(), MethodType::SetLoggingLevel);
    QCOMPARE(receivedSpy.at(0).at(0).toJsonObject().value("id"_L1).toInteger(), identifier);
    QCOMPARE(postedMessages(fakeServer, u"logging/setLevel"_s).constFirst().value("params"_L1).toObject(), (QJsonObject{{"level"_L1, u"warning"_s}}));
}

void McpProtocolClientProtocolManagerTest::shouldNotCompleteOrSetLevelWhenServerDoesNotSupportIt()
{
    FakeMcpHttpServer fakeServer;
    fakeServer.setHandler(createHandler());
    McpProtocolClientProtocolManager manager(createServer(fakeServer));
    initialize(manager);
    TextAutoGenerateTextMcpProtocolCore::McpProtocolPromptReference ref;
    ref.setName(u"review"_s);
    TextAutoGenerateTextMcpProtocolCore::McpProtocolCompleteRequestParams::Argument argument;
    argument.setName(u"language"_s);
    TextAutoGenerateTextMcpProtocolCore::McpProtocolCompleteRequestParams params;
    params.setRef(ref);
    params.setArgument(argument);
    QCOMPARE(manager.complete(params), -1);
    QCOMPARE(manager.setLoggingLevel(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel::Info), -1);
    QTest::qWait(100);
    QVERIFY(postedMessages(fakeServer, u"completion/complete"_s).isEmpty());
    QVERIFY(postedMessages(fakeServer, u"logging/setLevel"_s).isEmpty());
}

#include "moc_mcpprotocolclientprotocolmanagertest.cpp"
