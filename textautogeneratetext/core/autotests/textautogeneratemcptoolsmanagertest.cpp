/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemcptoolsmanagertest.h"
#include "core/mcp/textautogeneratemcptoolsmanager.h"
#include "fakemcphttpserver.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QPointer>
#include <QSignalSpy>
#include <QStandardPaths>
#include <QTcpSocket>
#include <QTest>
#include <TextAutoGenerateTextMcpProtocolCore/McpServerManager>
#include <TextAutoGenerateTextMcpProtocolCore/McpServerModel>
using namespace Qt::Literals::StringLiterals;
using TextAutoGenerateText::TextAutoGenerateMcpToolsManager;
QTEST_GUILESS_MAIN(TextAutoGenerateMcpToolsManagerTest)

namespace
{
QJsonObject tool(const QString &name, bool readOnly = false)
{
    QJsonObject obj{
        {"name"_L1, name},
        {"description"_L1, u"Description of %1"_s.arg(name)},
        {"inputSchema"_L1, QJsonObject{{"type"_L1, u"object"_s}, {"properties"_L1, QJsonObject{{"city"_L1, QJsonObject{{"type"_L1, u"string"_s}}}}}}}};
    if (readOnly) {
        obj["annotations"_L1] = QJsonObject{{"readOnlyHint"_L1, true}};
    }
    return obj;
}

// MCP server: tools are returned by tools/list, GET stream is kept open to send notifications
class FakeMcpServer
{
public:
    FakeMcpServer()
    {
        server.setHandler([this](const FakeMcpHttpServer::Request &request, QTcpSocket *socket) {
            if (request.method == "GET") {
                eventStream = socket;
                FakeMcpHttpServer::sendEventStream(socket, ": open\n\n", false);
                return;
            }
            if (request.method == "DELETE") {
                FakeMcpHttpServer::sendResponse(socket, 200);
                return;
            }
            const QJsonObject obj = request.json();
            const QString method = obj.value("method"_L1).toString();
            QJsonObject result;
            if (method == "initialize"_L1) {
                result = QJsonObject{{"protocolVersion"_L1, u"2025-11-25"_s},
                                     {"capabilities"_L1, QJsonObject{{"tools"_L1, QJsonObject{{"listChanged"_L1, true}}}}},
                                     {"serverInfo"_L1, QJsonObject{{"name"_L1, u"fake"_s}, {"version"_L1, u"1"_s}}}};
            } else if (method == "tools/list"_L1) {
                result = QJsonObject{{"tools"_L1, tools}};
            } else {
                FakeMcpHttpServer::sendResponse(socket, 202);
                return;
            }
            const QJsonObject response{{"jsonrpc"_L1, u"2.0"_s}, {"id"_L1, obj.value("id"_L1)}, {"result"_L1, result}};
            FakeMcpHttpServer::sendResponse(socket,
                                            200,
                                            "application/json",
                                            QJsonDocument(response).toJson(QJsonDocument::Compact),
                                            {{"Mcp-Session-Id"_ba, "session"_ba}});
        });
    }

    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpServer mcpServer(const QString &name) const
    {
        TextAutoGenerateTextMcpProtocolCore::McpServer mcpServer;
        mcpServer.setName(name);
        mcpServer.createUniqueIdentifier();
        mcpServer.setTransportType(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::StreamableHttp);
        TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
        settings.setServerUrl(server.url(u"/mcp"_s));
        mcpServer.setSettings(settings);
        return mcpServer;
    }

    FakeMcpHttpServer server;
    QJsonArray tools{tool(u"weather"_s, true), tool(u"get time"_s)};
    QPointer<QTcpSocket> eventStream;
};
}

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

#include "moc_textautogeneratemcptoolsmanagertest.cpp"
