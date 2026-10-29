/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpservertest.h"
#include "client/mcpserver.h"
#include <KConfig>
#include <KConfigGroup>
#include <QStandardPaths>
#include <QTest>

QTEST_GUILESS_MAIN(McpServerTest)
using namespace Qt::Literals::StringLiterals;
McpServerTest::McpServerTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void McpServerTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpServer w;
    QVERIFY(w.enabled());
    QVERIFY(w.name().isEmpty());
    QVERIFY(w.identifier().isEmpty());
    QVERIFY(w.iconName().isEmpty());
    QVERIFY(!w.filterTools());
    QVERIFY(w.allowedTools().isEmpty());
    QVERIFY(!w.isValid());
}

void McpServerTest::shouldVerifyValidValue()
{
    {
        TextAutoGenerateTextMcpProtocolCore::McpServer w;
        QVERIFY(!w.isValid());

        w.setName(u"foo"_s);
        QVERIFY(!w.isValid());

        w.setIdentifier("bla"_ba);
        QVERIFY(!w.isValid());

        TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings s;

        s.setServerUrl(QUrl(u"bla"_s));
        w.setSettings(s);
        QVERIFY(!w.isValid());

        w.setTransportType(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Sse);
        // Not a http url
        QVERIFY(!w.isValid());
        s.setServerUrl(QUrl(u"http://localhost:8080/sse"_s));
        w.setSettings(s);
        QVERIFY(w.isValid());
    }
    {
        TextAutoGenerateTextMcpProtocolCore::McpServer w;
        w.setTransportType(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Stdio);
        w.setName(u"foo"_s);
        w.setIdentifier("bla"_ba);
        QVERIFY(!w.isValid());
        TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings s;
        s.setArguments(u"ddd"_s);
        w.setSettings(s);
        QVERIFY(!w.isValid());
        s.setCommand(u"  "_s);
        w.setSettings(s);
        QVERIFY(!w.isValid());
        s.setCommand(u"foo"_s);
        w.setSettings(s);
        QVERIFY(w.isValid());
    }
    {
        TextAutoGenerateTextMcpProtocolCore::McpServer w;
        w.setTransportType(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::StreamableHttp);
        w.setName(u"foo"_s);
        w.setIdentifier("bla"_ba);
        QVERIFY(!w.isValid());
        TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings s;
        s.setServerUrl(QUrl(u"foo"_s));
        w.setSettings(s);
        QVERIFY(!w.isValid());
        s.setServerUrl(QUrl(u"https://example.com/mcp"_s));
        w.setSettings(s);
        QVERIFY(w.isValid());
    }
}

void McpServerTest::verifyConvertServerTypeToString()
{
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpServer::convertTransportTypeToString(
                 TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Sse),
             u"sse"_s);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpServer::convertTransportTypeToString(
                 TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Stdio),
             u"stdio"_s);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpServer::convertTransportTypeToString(
                 TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::StreamableHttp),
             u"streamablehttp"_s);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpServer::convertTransportTypeToString(
                 TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Unknown),
             QString());
}

void McpServerTest::verifyConvertServerTypeFromString()
{
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpServer::convertTransportTypeFromString(u"sse"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Sse);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpServer::convertTransportTypeFromString(u"stdio"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Stdio);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpServer::convertTransportTypeFromString(u"streamablehttp"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::StreamableHttp);

    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpServer::convertTransportTypeFromString(u"kde"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Unknown);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpServer::convertTransportTypeFromString(QString()),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Unknown);
}

void McpServerTest::shouldCompareServers()
{
    TextAutoGenerateTextMcpProtocolCore::McpServer first;
    first.setName(u"foo"_s);
    first.createUniqueIdentifier();
    TextAutoGenerateTextMcpProtocolCore::McpServer second = first;
    QCOMPARE(first, second);
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setCommand(u"bla"_s);
    second.setSettings(settings);
    QVERIFY(first != second);

    second = first;
    second.setFilterTools(true);
    QVERIFY(first != second);

    second = first;
    second.setAllowedTools({u"tool"_s});
    QVERIFY(first != second);
}

void McpServerTest::shouldFilterTools()
{
    TextAutoGenerateTextMcpProtocolCore::McpServer w;
    w.setAllowedTools({u"read_file"_s});
    // Not filtered: all tools are allowed
    QVERIFY(w.isToolAllowed(u"read_file"_s));
    QVERIFY(w.isToolAllowed(u"write_file"_s));

    w.setFilterTools(true);
    QVERIFY(w.isToolAllowed(u"read_file"_s));
    QVERIFY(!w.isToolAllowed(u"write_file"_s));

    w.setAllowedTools({});
    QVERIFY(!w.isToolAllowed(u"read_file"_s));
}

void McpServerTest::shouldLoadSaveAllowedTools()
{
    TextAutoGenerateTextMcpProtocolCore::McpServer server;
    server.setName(u"foo"_s);
    server.createUniqueIdentifier();
    server.setFilterTools(true);
    server.setAllowedTools({u"read_file"_s, u"list_directory"_s});

    // Not backed by a file
    KConfig config(QString(), KConfig::SimpleConfig);
    KConfigGroup group(&config, u"Server"_s);
    server.save(group);

    TextAutoGenerateTextMcpProtocolCore::McpServer loaded;
    loaded.load(group);
    QVERIFY(loaded.filterTools());
    QCOMPARE(loaded.allowedTools(), server.allowedTools());
}

#include "moc_mcpservertest.cpp"
