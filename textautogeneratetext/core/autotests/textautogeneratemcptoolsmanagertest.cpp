/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemcptoolsmanagertest.h"
#include "core/mcp/textautogeneratemcptoolsmanager.h"
#include "fakemcpserver.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QPointer>
#include <QSignalSpy>
#include <QStandardPaths>
#include <QTcpSocket>
#include <QTest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpServerManager>
#include <TextAutoGenerateTextMcpProtocolCore/McpServerModel>
using namespace Qt::Literals::StringLiterals;
using TextAutoGenerateText::TextAutoGenerateMcpToolsManager;
QTEST_GUILESS_MAIN(TextAutoGenerateMcpToolsManagerTest)

TextAutoGenerateMcpToolsManagerTest::TextAutoGenerateMcpToolsManagerTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateMcpToolsManagerTest::shouldSanitizeName()
{
    QCOMPARE(TextAutoGenerateMcpToolsManager::sanitizeName(u"get time"_s), "get_time"_ba);
    QCOMPARE(TextAutoGenerateMcpToolsManager::sanitizeName(u"a-b_c.d/é"_s), "a-b_c_d__"_ba);
}

void TextAutoGenerateMcpToolsManagerTest::shouldConnectAndListTools()
{
    FakeMcpServer fakeServer;
    TextAutoGenerateTextMcpProtocolCore::McpServerManager serverManager;
    const auto server = fakeServer.mcpServer(u"My Server"_s);
    serverManager.mcpServerModel()->addMcpServer(server);
    TextAutoGenerateMcpToolsManager manager(&serverManager);
    QCOMPARE(manager.status(server.identifier()), TextAutoGenerateMcpToolsManager::Status::Disconnected);

    QSignalSpy toolsChangedSpy(&manager, &TextAutoGenerateMcpToolsManager::toolsChanged);
    manager.connectServer(server.identifier());
    QCOMPARE(manager.status(server.identifier()), TextAutoGenerateMcpToolsManager::Status::Connecting);
    QTRY_COMPARE(toolsChangedSpy.count(), 1);
    QCOMPARE(manager.status(server.identifier()), TextAutoGenerateMcpToolsManager::Status::Connected);

    const auto tools = manager.tools(server.identifier());
    QCOMPARE(tools.count(), 2);
    QCOMPARE(tools.at(0).name, u"weather"_s);
    QCOMPARE(tools.at(0).exposedName, "My_Server__weather"_ba);
    QVERIFY(tools.at(0).readOnly);
    QCOMPARE(tools.at(1).exposedName, "My_Server__get_time"_ba);
    QVERIFY(!tools.at(1).readOnly);
    QVERIFY(manager.tool("My_Server__get_time"_ba).has_value());
    QCOMPARE(manager.tool("My_Server__get_time"_ba)->name, u"get time"_s);
    QVERIFY(manager.client(server.identifier()));

    const auto metaData = manager.toolsMetaData({server.identifier()});
    QCOMPARE(metaData.count(), 2);
    const QJsonObject function = metaData.at(0).value("function"_L1).toObject();
    QCOMPARE(metaData.at(0).value("type"_L1).toString(), u"function"_s);
    QCOMPARE(function.value("name"_L1).toString(), u"My_Server__weather"_s);
    QCOMPARE(function.value("description"_L1).toString(), u"Description of weather"_s);
    QCOMPARE(function.value("parameters"_L1).toObject().value("properties"_L1).toObject().keys(), QStringList{u"city"_s});
    // Other servers are not used
    QVERIFY(manager.toolsMetaData({"unknown"_ba}).isEmpty());
}

void TextAutoGenerateMcpToolsManagerTest::shouldReportErrorForInvalidServer()
{
    TextAutoGenerateTextMcpProtocolCore::McpServerManager serverManager;
    TextAutoGenerateMcpToolsManager manager(&serverManager);
    manager.connectServer("unknown"_ba);
    QCOMPARE(manager.status("unknown"_ba), TextAutoGenerateMcpToolsManager::Status::Error);
    QVERIFY(!manager.errorString("unknown"_ba).isEmpty());
}

void TextAutoGenerateMcpToolsManagerTest::shouldDisconnectWhenServerIsDisabled()
{
    FakeMcpServer fakeServer;
    TextAutoGenerateTextMcpProtocolCore::McpServerManager serverManager;
    const auto server = fakeServer.mcpServer(u"foo"_s);
    serverManager.mcpServerModel()->addMcpServer(server);
    TextAutoGenerateMcpToolsManager manager(&serverManager);
    manager.connectServer(server.identifier());
    QTRY_COMPARE(manager.tools(server.identifier()).count(), 2);

    QSignalSpy toolsChangedSpy(&manager, &TextAutoGenerateMcpToolsManager::toolsChanged);
    auto model = serverManager.mcpServerModel();
    QVERIFY(model->setData(model->index(0), Qt::Unchecked, Qt::CheckStateRole));
    QCOMPARE(toolsChangedSpy.count(), 1);
    QCOMPARE(manager.status(server.identifier()), TextAutoGenerateMcpToolsManager::Status::Disconnected);
    QVERIFY(manager.tools(server.identifier()).isEmpty());
    QVERIFY(!manager.client(server.identifier()));
    // Session is closed
    QTRY_COMPARE(fakeServer.server.requests("DELETE").count(), 1);
}

void TextAutoGenerateMcpToolsManagerTest::shouldRefreshToolsWhenListChanged()
{
    FakeMcpServer fakeServer;
    TextAutoGenerateTextMcpProtocolCore::McpServerManager serverManager;
    const auto server = fakeServer.mcpServer(u"foo"_s);
    serverManager.mcpServerModel()->addMcpServer(server);
    TextAutoGenerateMcpToolsManager manager(&serverManager);
    manager.connectServer(server.identifier());
    QTRY_COMPARE(manager.tools(server.identifier()).count(), 2);
    QTRY_VERIFY(fakeServer.eventStream);

    fakeServer.tools.append(tool(u"new_tool"_s));
    const QJsonObject notification{{"jsonrpc"_L1, u"2.0"_s}, {"method"_L1, u"notifications/tools/list_changed"_s}};
    FakeMcpHttpServer::sendEvents(fakeServer.eventStream, FakeMcpHttpServer::jsonEvent(notification));
    QTRY_COMPARE(manager.tools(server.identifier()).count(), 3);
    QCOMPARE(manager.tools(server.identifier()).at(2).exposedName, "foo__new_tool"_ba);
}

void TextAutoGenerateMcpToolsManagerTest::shouldCreateUniqueNames()
{
    FakeMcpServer fakeServer;
    TextAutoGenerateTextMcpProtocolCore::McpServerManager serverManager;
    // Same name for two servers
    const auto first = fakeServer.mcpServer(u"foo"_s);
    const auto second = fakeServer.mcpServer(u"foo"_s);
    serverManager.mcpServerModel()->addMcpServer(first);
    serverManager.mcpServerModel()->addMcpServer(second);
    TextAutoGenerateMcpToolsManager manager(&serverManager);
    manager.connectServer(first.identifier());
    QTRY_COMPARE(manager.tools(first.identifier()).count(), 2);
    manager.connectServer(second.identifier());
    QTRY_COMPARE(manager.tools(second.identifier()).count(), 2);

    QSet<QByteArray> names;
    for (const auto &identifier : {first.identifier(), second.identifier()}) {
        for (const auto &t : manager.tools(identifier)) {
            QVERIFY(t.exposedName.size() <= 64);
            names.insert(t.exposedName);
        }
    }
    QCOMPARE(names.count(), 4);
}

void TextAutoGenerateMcpToolsManagerTest::shouldConvertToolIdentifiers()
{
    QCOMPARE(TextAutoGenerateMcpToolsManager::toolIdentifier("abc"_ba), "mcp:abc"_ba);
    QVERIFY(TextAutoGenerateMcpToolsManager::isMcpToolIdentifier("mcp:abc"_ba));
    QVERIFY(!TextAutoGenerateMcpToolsManager::isMcpToolIdentifier("example_tool"_ba));
    QCOMPARE(TextAutoGenerateMcpToolsManager::serverIdentifier("mcp:abc"_ba), "abc"_ba);
    QVERIFY(TextAutoGenerateMcpToolsManager::serverIdentifier("example_tool"_ba).isEmpty());
    QCOMPARE(TextAutoGenerateMcpToolsManager::serverIdentifiers({"example_tool"_ba, "mcp:a"_ba, "mcp:b"_ba}), QList<QByteArray>({"a"_ba, "b"_ba}));
}

void TextAutoGenerateMcpToolsManagerTest::shouldPrepareServers()
{
    FakeMcpServer fakeServer;
    TextAutoGenerateTextMcpProtocolCore::McpServerManager serverManager;
    const auto server = fakeServer.mcpServer(u"foo"_s);
    serverManager.mcpServerModel()->addMcpServer(server);
    TextAutoGenerateMcpToolsManager manager(&serverManager);
    QObject context;
    int callbackCount = 0;
    int toolCount = -1;
    manager.prepareServers({server.identifier()}, &context, [&]() {
        ++callbackCount;
        toolCount = manager.tools(server.identifier()).count();
    });
    // Tools are not loaded yet
    QCOMPARE(callbackCount, 0);
    QTRY_COMPARE(callbackCount, 1);
    // Callback is called when tools are loaded
    QCOMPARE(toolCount, 2);
    QVERIFY(manager.isReady(server.identifier()));

    // Already ready: called directly
    manager.prepareServers({server.identifier()}, &context, [&]() {
        ++callbackCount;
    });
    QCOMPARE(callbackCount, 2);
    QTest::qWait(50);
    QCOMPARE(callbackCount, 2);
}

void TextAutoGenerateMcpToolsManagerTest::shouldPrepareInvalidServer()
{
    TextAutoGenerateTextMcpProtocolCore::McpServerManager serverManager;
    TextAutoGenerateMcpToolsManager manager(&serverManager);
    QObject context;
    int callbackCount = 0;
    // Error: nothing to wait
    manager.prepareServers({"unknown"_ba}, &context, [&]() {
        ++callbackCount;
    });
    QCOMPARE(callbackCount, 1);
}

void TextAutoGenerateMcpToolsManagerTest::shouldNotCallCallbackWhenContextIsDeleted()
{
    FakeMcpServer fakeServer;
    TextAutoGenerateTextMcpProtocolCore::McpServerManager serverManager;
    const auto server = fakeServer.mcpServer(u"foo"_s);
    serverManager.mcpServerModel()->addMcpServer(server);
    TextAutoGenerateMcpToolsManager manager(&serverManager);
    auto context = new QObject;
    int callbackCount = 0;
    manager.prepareServers({server.identifier()}, context, [&]() {
        ++callbackCount;
    });
    delete context;
    QTRY_VERIFY(manager.isReady(server.identifier()));
    QTest::qWait(50);
    QCOMPARE(callbackCount, 0);
}

void TextAutoGenerateMcpToolsManagerTest::shouldCallCallbackAfterTimeout()
{
    // Server never answers
    FakeMcpHttpServer silentServer;
    silentServer.setHandler([](const FakeMcpHttpServer::Request &, QTcpSocket *) { });
    TextAutoGenerateTextMcpProtocolCore::McpServerManager serverManager;
    TextAutoGenerateTextMcpProtocolCore::McpServer server;
    server.setName(u"silent"_s);
    server.createUniqueIdentifier();
    server.setTransportType(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::StreamableHttp);
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setServerUrl(silentServer.url(u"/mcp"_s));
    server.setSettings(settings);
    serverManager.mcpServerModel()->addMcpServer(server);
    TextAutoGenerateMcpToolsManager manager(&serverManager);
    QObject context;
    int callbackCount = 0;
    manager.prepareServers(
        {server.identifier()},
        &context,
        [&]() {
            ++callbackCount;
        },
        std::chrono::milliseconds(200));
    QTRY_COMPARE(callbackCount, 1);
    QCOMPARE(manager.status(server.identifier()), TextAutoGenerateMcpToolsManager::Status::Connecting);
}

void TextAutoGenerateMcpToolsManagerTest::shouldAnswerElicitationRequest()
{
    {
        // Not announced without handler
        FakeMcpServer fakeServer;
        TextAutoGenerateTextMcpProtocolCore::McpServerManager serverManager;
        const auto server = fakeServer.mcpServer(u"foo"_s);
        serverManager.mcpServerModel()->addMcpServer(server);
        TextAutoGenerateMcpToolsManager manager(&serverManager);
        manager.connectServer(server.identifier());
        QTRY_COMPARE(manager.tools(server.identifier()).count(), 2);
        const QJsonObject initialize = fakeServer.receivedRequests.constFirst();
        QCOMPARE(initialize.value("method"_L1).toString(), u"initialize"_s);
        QVERIFY(!initialize.value("params"_L1).toObject().value("capabilities"_L1).toObject().contains("elicitation"_L1));
    }
    FakeMcpServer fakeServer;
    TextAutoGenerateTextMcpProtocolCore::McpServerManager serverManager;
    const auto server = fakeServer.mcpServer(u"foo"_s);
    serverManager.mcpServerModel()->addMcpServer(server);
    TextAutoGenerateMcpToolsManager manager(&serverManager);
    QList<TextAutoGenerateMcpToolsManager::ElicitationInfo> infos;
    manager.setElicitationHandler([&infos](const TextAutoGenerateMcpToolsManager::ElicitationInfo &info,
                                           const std::function<void(const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult &)> &answer) {
        infos.append(info);
        TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult result;
        result.setAction(TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult::Action::Accept);
        answer(result);
    });
    manager.connectServer(server.identifier());
    QTRY_COMPARE(manager.tools(server.identifier()).count(), 2);
    const QJsonObject initialize = fakeServer.receivedRequests.constFirst();
    QVERIFY(initialize.value("params"_L1).toObject().value("capabilities"_L1).toObject().contains("elicitation"_L1));
    QTRY_VERIFY(fakeServer.eventStream);

    const QJsonObject elicit{{"jsonrpc"_L1, u"2.0"_s},
                             {"id"_L1, u"srv-1"_s},
                             {"method"_L1, u"elicitation/create"_s},
                             {"params"_L1,
                              QJsonObject{{"mode"_L1, u"form"_s},
                                          {"message"_L1, u"Name?"_s},
                                          {"requestedSchema"_L1, QJsonObject{{"type"_L1, u"object"_s}, {"properties"_L1, QJsonObject{}}}}}}};
    FakeMcpHttpServer::sendEvents(fakeServer.eventStream, FakeMcpHttpServer::jsonEvent(elicit));
    QTRY_COMPARE(infos.count(), 1);
    QCOMPARE(infos.at(0).serverName, u"foo"_s);
    QJsonObject response;
    QTRY_VERIFY([&]() {
        for (const auto &obj : std::as_const(fakeServer.receivedRequests)) {
            if (!obj.contains("method"_L1) && obj.value("id"_L1).toString() == u"srv-1"_s) {
                response = obj;
                return true;
            }
        }
        return false;
    }());
    QCOMPARE(response.value("result"_L1).toObject().value("action"_L1).toString(), u"accept"_s);
}

#include "moc_textautogeneratemcptoolsmanagertest.cpp"
