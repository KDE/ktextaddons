/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemcptoolcalljobtest.h"
#include "core/mcp/textautogeneratemcptoolcalljob.h"
#include "core/mcp/textautogeneratemcptoolsmanager.h"
#include "core/tools/textautogeneratetoolcalljob.h"
#include "fakemcpserver.h"
#include <QSignalSpy>
#include <QStandardPaths>
#include <QTest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCallToolResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpServerManager>
#include <TextAutoGenerateTextMcpProtocolCore/McpServerModel>
using TextAutoGenerateText::TextAutoGenerateMcpToolCallJob;
using TextAutoGenerateText::TextAutoGenerateMcpToolsManager;
using TextAutoGenerateTextMcpProtocolCore::McpProtocolCallToolResult;
QTEST_GUILESS_MAIN(TextAutoGenerateMcpToolCallJobTest)

namespace
{
TextAutoGenerateText::TextAutoGenerateTextToolPlugin::TextToolPluginInfo
callTool(TextAutoGenerateMcpToolsManager *manager, const QByteArray &toolName, const QJsonObject &arguments)
{
    TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo info;
    info.toolName = toolName;
    info.arguments = arguments;
    auto job = new TextAutoGenerateText::TextAutoGenerateToolCallJob("chat"_ba, "uuid"_ba, {info});
    job->setTextAutoGenerateMcpToolsManager(manager);
    QSignalSpy finishedSpy(job, &TextAutoGenerateText::TextAutoGenerateToolCallJob::finished);
    job->start();
    // Signal can be emitted synchronously
    if (finishedSpy.isEmpty() && !finishedSpy.wait(5000)) {
        return {};
    }
    return finishedSpy.at(0).at(0).value<TextAutoGenerateText::TextAutoGenerateTextToolPlugin::TextToolPluginInfo>();
}
}

TextAutoGenerateMcpToolCallJobTest::TextAutoGenerateMcpToolCallJobTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateMcpToolCallJobTest::shouldConvertResultToText()
{
    const QJsonObject text1{{"type"_L1, u"text"_s}, {"text"_L1, u"first"_s}};
    const QJsonObject image{{"type"_L1, u"image"_s}, {"data"_L1, u"AAAA"_s}, {"mimeType"_L1, u"image/png"_s}};
    const QJsonObject link{{"type"_L1, u"resource_link"_s}, {"name"_L1, u"file"_s}, {"uri"_L1, u"file:///tmp/foo"_s}};
    auto result = McpProtocolCallToolResult::fromJson(QJsonObject{{"content"_L1, QJsonArray{text1, image, link}}});
    QCOMPARE(TextAutoGenerateMcpToolCallJob::resultToText(result), u"first\nfile:///tmp/foo"_s);

    // Error
    result = McpProtocolCallToolResult::fromJson(QJsonObject{{"content"_L1, QJsonArray{text1}}, {"isError"_L1, true}});
    QVERIFY(TextAutoGenerateMcpToolCallJob::resultToText(result).contains(u"first"_s));
    QVERIFY(TextAutoGenerateMcpToolCallJob::resultToText(result) != u"first"_s);

    // Only structured content
    result = McpProtocolCallToolResult::fromJson(QJsonObject{{"content"_L1, QJsonArray{}}, {"structuredContent"_L1, QJsonObject{{"temperature"_L1, 21}}}});
    QCOMPARE(TextAutoGenerateMcpToolCallJob::resultToText(result), uR"({"temperature":21})"_s);
}

void TextAutoGenerateMcpToolCallJobTest::shouldCallTool()
{
    FakeMcpServer fakeServer;
    TextAutoGenerateTextMcpProtocolCore::McpServerManager serverManager;
    const auto server = fakeServer.mcpServer(u"foo"_s);
    serverManager.mcpServerModel()->addMcpServer(server);
    TextAutoGenerateMcpToolsManager manager(&serverManager);
    manager.connectServer(server.identifier());
    QTRY_VERIFY(manager.tool("foo__get_time"_ba).has_value());

    const auto info = callTool(&manager, "foo__get_time"_ba, QJsonObject{{"city"_L1, u"Paris"_s}, {"days"_L1, 3}});
    // MCP name is used, arguments keep their type
    QCOMPARE(info.content, uR"(get time {"city":"Paris","days":3})"_s);
    QCOMPARE(info.chatId, "chat"_ba);
    QCOMPARE(info.messageUuid, "uuid"_ba);
}

void TextAutoGenerateMcpToolCallJobTest::shouldReportToolError()
{
    FakeMcpServer fakeServer;
    fakeServer.tools.append(tool(u"failing"_s));
    TextAutoGenerateTextMcpProtocolCore::McpServerManager serverManager;
    const auto server = fakeServer.mcpServer(u"foo"_s);
    serverManager.mcpServerModel()->addMcpServer(server);
    TextAutoGenerateMcpToolsManager manager(&serverManager);
    manager.connectServer(server.identifier());
    QTRY_VERIFY(manager.tool("foo__failing"_ba).has_value());

    const auto info = callTool(&manager, "foo__failing"_ba, {});
    QVERIFY(info.content.contains(u"failing"_s));
    QVERIFY(!info.content.startsWith(u"failing"_s));
}

void TextAutoGenerateMcpToolCallJobTest::shouldReportUnavailableTool()
{
    TextAutoGenerateTextMcpProtocolCore::McpServerManager serverManager;
    TextAutoGenerateMcpToolsManager manager(&serverManager);
    // Not a MCP tool and not a plugin
    const auto info = callTool(&manager, "unknown__tool"_ba, {});
    QVERIFY(info.content.contains(u"unknown__tool"_s));
    QCOMPARE(info.chatId, "chat"_ba);
}

void TextAutoGenerateMcpToolCallJobTest::shouldAskConfirmation()
{
    FakeMcpServer fakeServer;
    TextAutoGenerateTextMcpProtocolCore::McpServerManager serverManager;
    const auto server = fakeServer.mcpServer(u"foo"_s);
    serverManager.mcpServerModel()->addMcpServer(server);
    TextAutoGenerateMcpToolsManager manager(&serverManager);
    manager.connectServer(server.identifier());
    QTRY_VERIFY(manager.tool("foo__get_time"_ba).has_value());

    QList<TextAutoGenerateMcpToolsManager::ToolConfirmationInfo> askedTools;
    TextAutoGenerateMcpToolsManager::ToolConfirmation answer = TextAutoGenerateMcpToolsManager::ToolConfirmation::Deny;
    manager.setConfirmationHandler([&](const TextAutoGenerateMcpToolsManager::ToolConfirmationInfo &info,
                                       const std::function<void(TextAutoGenerateMcpToolsManager::ToolConfirmation)> &reply) {
        askedTools.append(info);
        reply(answer);
    });

    // Refused: LLM gets information, server is not called
    auto info = callTool(&manager, "foo__get_time"_ba, QJsonObject{{"city"_L1, u"Paris"_s}});
    QCOMPARE(askedTools.count(), 1);
    QCOMPARE(askedTools.at(0).serverName, u"foo"_s);
    QCOMPARE(askedTools.at(0).tool.name, u"get time"_s);
    QCOMPARE(askedTools.at(0).arguments, QJsonObject({{"city"_L1, u"Paris"_s}}));
    QVERIFY(info.content.contains(u"get time"_s));
    QVERIFY(!info.content.startsWith(u"get time"_s));

    // Accepted
    answer = TextAutoGenerateMcpToolsManager::ToolConfirmation::Allow;
    info = callTool(&manager, "foo__get_time"_ba, {});
    QCOMPARE(askedTools.count(), 2);
    QCOMPARE(info.content, u"get time {}"_s);

    // Read only tool: no confirmation
    info = callTool(&manager, "foo__weather"_ba, {});
    QCOMPARE(askedTools.count(), 2);
    QCOMPARE(info.content, u"weather {}"_s);

    // Always allowed: asked only once
    QVERIFY(!manager.isServerAlwaysAllowed(server.identifier()));
    answer = TextAutoGenerateMcpToolsManager::ToolConfirmation::AlwaysAllowServer;
    info = callTool(&manager, "foo__get_time"_ba, {});
    QCOMPARE(askedTools.count(), 3);
    QVERIFY(manager.isServerAlwaysAllowed(server.identifier()));
    info = callTool(&manager, "foo__get_time"_ba, {});
    QCOMPARE(askedTools.count(), 3);
    QCOMPARE(info.content, u"get time {}"_s);
    manager.setServerAlwaysAllowed(server.identifier(), false);
    QVERIFY(!manager.isServerAlwaysAllowed(server.identifier()));
}

#include "moc_textautogeneratemcptoolcalljobtest.cpp"
