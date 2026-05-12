/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpservertest.h"
#include "server/mcpserver.h"
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
    QVERIFY(w.serverUrl().isEmpty());
    QVERIFY(w.enabled());
    QVERIFY(w.name().isEmpty());
    QVERIFY(w.identifier().isEmpty());
    QVERIFY(!w.isValid());
}

void McpServerTest::shouldVerifyValidValue()
{
    TextAutoGenerateTextMcpProtocolCore::McpServer w;
    QVERIFY(!w.isValid());

    w.setName(u"foo"_s);
    QVERIFY(!w.isValid());

    w.setIdentifier("bla"_ba);
    QVERIFY(!w.isValid());

    w.setServerUrl(QUrl(u"bla"_s));
    QVERIFY(!w.isValid());

    w.setTransportType(TextAutoGenerateTextMcpProtocolCore::McpServer::TransportType::Sse);
    QVERIFY(w.isValid());
}

void McpServerTest::verifyConvertServerTypeToString()
{
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpServer::convertTransportTypeToString(TextAutoGenerateTextMcpProtocolCore::McpServer::TransportType::Sse),
             u"sse"_s);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpServer::convertTransportTypeToString(TextAutoGenerateTextMcpProtocolCore::McpServer::TransportType::Stdio),
             u"stdio"_s);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpServer::convertTransportTypeToString(
                 TextAutoGenerateTextMcpProtocolCore::McpServer::TransportType::StreamableHttp),
             u"streamablehttp"_s);
    QCOMPARE(
        TextAutoGenerateTextMcpProtocolCore::McpServer::convertTransportTypeToString(TextAutoGenerateTextMcpProtocolCore::McpServer::TransportType::Unknown),
        QString());
}

void McpServerTest::verifyConvertServerTypeFromString()
{
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpServer::convertTransportTypeFromString(u"sse"_s),
             TextAutoGenerateTextMcpProtocolCore::McpServer::TransportType::Sse);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpServer::convertTransportTypeFromString(u"stdio"_s),
             TextAutoGenerateTextMcpProtocolCore::McpServer::TransportType::Stdio);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpServer::convertTransportTypeFromString(u"streamablehttp"_s),
             TextAutoGenerateTextMcpProtocolCore::McpServer::TransportType::StreamableHttp);

    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpServer::convertTransportTypeFromString(u"kde"_s),
             TextAutoGenerateTextMcpProtocolCore::McpServer::TransportType::Unknown);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpServer::convertTransportTypeFromString(QString()),
             TextAutoGenerateTextMcpProtocolCore::McpServer::TransportType::Unknown);
}

#include "moc_mcpservertest.cpp"
