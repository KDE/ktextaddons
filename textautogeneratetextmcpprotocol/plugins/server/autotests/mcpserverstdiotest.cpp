/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserverstdiotest.h"
#include "stdio/mcpclientstdioplugininterface.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>
#include <QSignalSpy>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpServerStdioTest)

namespace
{
QJsonObject jsonRequest(const QString &method, int id, const QJsonObject &params = {})
{
    QJsonObject obj{{"jsonrpc"_L1, u"2.0"_s}, {"id"_L1, id}, {"method"_L1, method}};
    if (!params.isEmpty()) {
        obj["params"_L1] = params;
    }
    return obj;
}

QJsonObject initializeRequest(int id)
{
    return jsonRequest(u"initialize"_s,
                       id,
                       QJsonObject{{"protocolVersion"_L1, u"2025-11-25"_s},
                                   {"capabilities"_L1, QJsonObject{}},
                                   {"clientInfo"_L1, QJsonObject{{"name"_L1, u"test"_s}, {"version"_L1, u"1"_s}}}});
}

QByteArray line(const QJsonObject &obj)
{
    return QJsonDocument(obj).toJson(QJsonDocument::Compact) + '\n';
}

QString helperPath()
{
    return QStringLiteral(MCPSERVERSTDIOHELPER_PATH);
}

// Read one line of stdout, it must be a json object
QJsonObject readMessage(QProcess &process)
{
    while (!process.canReadLine()) {
        if (!process.waitForReadyRead(5000)) {
            return {};
        }
    }
    const QByteArray data = process.readLine();
    QJsonParseError parseError;
    const QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "Invalid line in stdout:" << data;
        return {};
    }
    return doc.object();
}

void startHelper(QProcess &process)
{
    // Logs must go to stderr: stdout contains only messages
    process.setProcessChannelMode(QProcess::SeparateChannels);
    process.start(helperPath(), QStringList());
    QVERIFY(process.waitForStarted());
}
}

McpServerStdioTest::McpServerStdioTest(QObject *parent)
    : QObject{parent}
{
}

void McpServerStdioTest::shouldExchangeMessagesWithClient()
{
    McpClientStdioPluginInterface client;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setCommand(helperPath());
    client.setSettings(settings);
    QSignalSpy startedSpy(&client, &McpClientStdioPluginInterface::started);
    QSignalSpy receivedSpy(&client, &McpClientStdioPluginInterface::received);
    QSignalSpy finishedSpy(&client, &McpClientStdioPluginInterface::finished);
    client.start();
    QTRY_COMPARE(startedSpy.count(), 1);

    client.send(initializeRequest(1));
    QTRY_COMPARE(receivedSpy.count(), 1);
    const QJsonObject initializeResponse = receivedSpy.at(0).at(0).toJsonObject();
    QCOMPARE(initializeResponse.value("id"_L1).toInt(), 1);
    const QJsonObject result = initializeResponse.value("result"_L1).toObject();
    QCOMPARE(result.value("protocolVersion"_L1).toString(), u"2025-11-25"_s);
    QCOMPARE(result.value("serverInfo"_L1).toObject().value("name"_L1).toString(), u"mcpserverstdiohelper"_s);

    client.send(QJsonObject{{"jsonrpc"_L1, u"2.0"_s}, {"method"_L1, u"notifications/initialized"_s}});
    client.send(jsonRequest(u"ping"_s, 2));
    QTRY_COMPARE(receivedSpy.count(), 2);
    QCOMPARE(receivedSpy.at(1).at(0).toJsonObject().value("id"_L1).toInt(), 2);
    QVERIFY(receivedSpy.at(1).at(0).toJsonObject().contains("result"_L1));

    client.send(jsonRequest(u"tools/list"_s, 3));
    QTRY_COMPARE(receivedSpy.count(), 3);
    QVERIFY(receivedSpy.at(2).at(0).toJsonObject().value("result"_L1).toObject().value("tools"_L1).isArray());

    client.send(jsonRequest(u"does/not/exist"_s, 4));
    QTRY_COMPARE(receivedSpy.count(), 4);
    QCOMPARE(receivedSpy.at(3).at(0).toJsonObject().value("error"_L1).toObject().value("code"_L1).toInt(), -32601);

    client.stop();
    QTRY_COMPARE(finishedSpy.count(), 1);
}

void McpServerStdioTest::shouldExitWhenStdinIsClosed()
{
    QProcess process;
    startHelper(process);
    process.closeWriteChannel();
    QVERIFY(process.waitForFinished(5000));
    QCOMPARE(process.exitStatus(), QProcess::NormalExit);
    QCOMPARE(process.exitCode(), 0);
    // Nothing written in stdout
    QVERIFY(process.readAllStandardOutput().isEmpty());
}

void McpServerStdioTest::shouldIgnoreInvalidJson()
{
    QProcess process;
    startHelper(process);
    process.write("not json\n\n"_ba + line(initializeRequest(1)));
    const QJsonObject response = readMessage(process);
    QCOMPARE(response.value("id"_L1).toInt(), 1);
    QVERIFY(response.contains("result"_L1));
    process.closeWriteChannel();
    QVERIFY(process.waitForFinished(5000));
    QCOMPARE(process.exitCode(), 0);
}

void McpServerStdioTest::shouldReadMessageSplitInSeveralWrites()
{
    QProcess process;
    startHelper(process);
    const QByteArray data = line(initializeRequest(1)) + line(jsonRequest(u"ping"_s, 2));
    const qsizetype middle = data.size() / 3;
    process.write(data.left(middle));
    QVERIFY(process.waitForBytesWritten());
    QTest::qWait(100);
    process.write(data.mid(middle));
    QCOMPARE(readMessage(process).value("id"_L1).toInt(), 1);
    QCOMPARE(readMessage(process).value("id"_L1).toInt(), 2);
    process.closeWriteChannel();
    QVERIFY(process.waitForFinished(5000));
}

#include "moc_mcpserverstdiotest.cpp"
