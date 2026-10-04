/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientstdiotest.h"
#include "stdio/mcpclientstdioplugininterface.h"
#include <QJsonObject>
#include <QSignalSpy>
#include <QStandardPaths>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpClientStdioTest)

McpClientStdioTest::McpClientStdioTest(QObject *parent)
    : QObject{parent}
{
}

void McpClientStdioTest::shouldSendAndReceiveMessages()
{
    // "cat" sends back each line: it checks framing of messages
    const QString cat = QStandardPaths::findExecutable(u"cat"_s);
    if (cat.isEmpty()) {
        QSKIP("cat not found");
    }
    McpClientStdioPluginInterface client;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setCommand(cat);
    client.setSettings(settings);
    QSignalSpy startedSpy(&client, &McpClientStdioPluginInterface::started);
    QSignalSpy receivedSpy(&client, &McpClientStdioPluginInterface::received);
    QSignalSpy finishedSpy(&client, &McpClientStdioPluginInterface::finished);
    client.start();
    QTRY_COMPARE(startedSpy.count(), 1);

    // Embedded newline must be escaped, message must stay on one line
    const QJsonObject first{{"jsonrpc"_L1, u"2.0"_s}, {"id"_L1, 1}, {"method"_L1, u"ping"_s}, {"params"_L1, QJsonObject{{"text"_L1, u"a\nb"_s}}}};
    const QJsonObject second{{"jsonrpc"_L1, u"2.0"_s}, {"method"_L1, u"notifications/initialized"_s}};
    client.send(first);
    client.send(second);
    QTRY_COMPARE(receivedSpy.count(), 2);
    QCOMPARE(receivedSpy.at(0).at(0).toJsonObject(), first);
    QCOMPARE(receivedSpy.at(1).at(0).toJsonObject(), second);

    client.stop();
    QTRY_COMPARE(finishedSpy.count(), 1);
}

void McpClientStdioTest::shouldFinishWhenProcessFailedToStart()
{
    McpClientStdioPluginInterface client;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setCommand(u"/does/not/exist/mcp-server"_s);
    client.setSettings(settings);
    QSignalSpy errorSpy(&client, &McpClientStdioPluginInterface::error);
    QSignalSpy finishedSpy(&client, &McpClientStdioPluginInterface::finished);
    client.start();
    QTRY_COMPARE(finishedSpy.count(), 1);
    QCOMPARE(errorSpy.count(), 1);
}

void McpClientStdioTest::shouldSupportQuotedArguments()
{
    const QString sh = QStandardPaths::findExecutable(u"sh"_s);
    if (sh.isEmpty()) {
        QSKIP("sh not found");
    }
    McpClientStdioPluginInterface client;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setCommand(sh);
    // "cat -" must be one argument
    settings.setArguments(u"-c 'cat -'"_s);
    client.setSettings(settings);
    QSignalSpy startedSpy(&client, &McpClientStdioPluginInterface::started);
    QSignalSpy receivedSpy(&client, &McpClientStdioPluginInterface::received);
    client.start();
    QTRY_COMPARE(startedSpy.count(), 1);
    const QJsonObject message{{"jsonrpc"_L1, u"2.0"_s}, {"method"_L1, u"notifications/initialized"_s}};
    client.send(message);
    QTRY_COMPARE(receivedSpy.count(), 1);
    QCOMPARE(receivedSpy.at(0).at(0).toJsonObject(), message);
    client.stop();
}

void McpClientStdioTest::shouldRejectInvalidArguments()
{
    McpClientStdioPluginInterface client;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setCommand(u"cat"_s);
    settings.setArguments(u"'unterminated"_s);
    client.setSettings(settings);
    QSignalSpy startedSpy(&client, &McpClientStdioPluginInterface::started);
    QSignalSpy errorSpy(&client, &McpClientStdioPluginInterface::error);
    QSignalSpy finishedSpy(&client, &McpClientStdioPluginInterface::finished);
    client.start();
    QCOMPARE(errorSpy.count(), 1);
    QCOMPARE(finishedSpy.count(), 1);
    QTest::qWait(100);
    QCOMPARE(startedSpy.count(), 0);
}

#include "moc_mcpclientstdiotest.cpp"
