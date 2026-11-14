/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpexportclaudecodetest.h"
#include "importexport/mcpexportclaudecode.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTemporaryDir>
#include <QTest>

QTEST_GUILESS_MAIN(McpExportClaudeCodeTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;

namespace
{
McpServer createServer(const QString &name, McpProtocolPlugin::TransportType type, const McpProtocolSettings &settings)
{
    McpServer server;
    server.setName(name);
    server.createUniqueIdentifier();
    server.setTransportType(type);
    server.setSettings(settings);
    return server;
}

McpServer createStdioServer(const QString &name = u"git"_s)
{
    McpProtocolSettings settings;
    settings.setCommand(u"uvx"_s);
    settings.setArguments(u"mcp-server-git --repository \"/tmp/my repo\""_s);
    settings.setEnvironments({{u"FOO"_s, u"bar"_s}});
    return createServer(name, McpProtocolPlugin::TransportType::Stdio, settings);
}

QJsonObject readJson(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        return {};
    }
    return QJsonDocument::fromJson(file.readAll()).object();
}

void writeFile(const QString &path, const QByteArray &data)
{
    QFile file(path);
    QVERIFY(file.open(QIODevice::WriteOnly));
    file.write(data);
}
}

McpExportClaudeCodeTest::McpExportClaudeCodeTest(QObject *parent)
    : QObject{parent}
{
}

void McpExportClaudeCodeTest::shouldHaveDefaultValues()
{
    const McpExportClaudeCode w;
    QVERIFY(!w.isValid());
    QVERIFY(!w.exportServer());
}

void McpExportClaudeCodeTest::shouldNotExportInvalidServer()
{
    QTemporaryDir dir;
    QVERIFY(dir.isValid());
    const QString path = dir.filePath(u".mcp.json"_s);

    // Valid server without path
    McpExportClaudeCode w;
    w.setServer(createStdioServer());
    QVERIFY(!w.isValid());
    QVERIFY(!w.exportServer());

    // Path with invalid server (no command)
    w.setServer(createServer(u"invalid"_s, McpProtocolPlugin::TransportType::Stdio, {}));
    w.setPath(path);
    QVERIFY(!w.isValid());
    QVERIFY(!w.exportServer());
    QVERIFY(!QFile::exists(path));
}

void McpExportClaudeCodeTest::shouldExportStdioServer()
{
    QTemporaryDir dir;
    QVERIFY(dir.isValid());
    const QString path = dir.filePath(u".mcp.json"_s);

    McpExportClaudeCode w;
    w.setServer(createStdioServer());
    w.setPath(path);
    QVERIFY(w.isValid());
    QVERIFY(w.exportServer());

    const QJsonObject root = readJson(path);
    const QJsonObject mcpServers = root.value("mcpServers"_L1).toObject();
    QCOMPARE(mcpServers.keys(), QStringList{u"git"_s});
    const QJsonObject server = mcpServers.value("git"_L1).toObject();
    QCOMPARE(server.value("type"_L1).toString(), u"stdio"_s);
    QCOMPARE(server.value("command"_L1).toString(), u"uvx"_s);
    // Quoted argument must be kept as one argument
    const QJsonArray expectedArgs{u"mcp-server-git"_s, u"--repository"_s, u"/tmp/my repo"_s};
    QCOMPARE(server.value("args"_L1).toArray(), expectedArgs);
    const QJsonObject expectedEnv{{u"FOO"_s, u"bar"_s}};
    QCOMPARE(server.value("env"_L1).toObject(), expectedEnv);
}

void McpExportClaudeCodeTest::shouldExportStdioServerWithoutArguments()
{
    QTemporaryDir dir;
    QVERIFY(dir.isValid());
    const QString path = dir.filePath(u".mcp.json"_s);

    McpProtocolSettings settings;
    settings.setCommand(u"my-server"_s);
    McpExportClaudeCode w;
    w.setServer(createServer(u"local"_s, McpProtocolPlugin::TransportType::Stdio, settings));
    w.setPath(path);
    QVERIFY(w.exportServer());

    const QJsonObject server = readJson(path).value("mcpServers"_L1).toObject().value("local"_L1).toObject();
    QCOMPARE(server.value("command"_L1).toString(), u"my-server"_s);
    QVERIFY(!server.contains("args"_L1));
    QVERIFY(!server.contains("env"_L1));
}

void McpExportClaudeCodeTest::shouldNotExportStdioServerWithInvalidArguments()
{
    QTemporaryDir dir;
    QVERIFY(dir.isValid());
    const QString path = dir.filePath(u".mcp.json"_s);

    McpProtocolSettings settings;
    settings.setCommand(u"my-server"_s);
    settings.setArguments(u"--name \"unterminated"_s);
    McpExportClaudeCode w;
    w.setServer(createServer(u"local"_s, McpProtocolPlugin::TransportType::Stdio, settings));
    w.setPath(path);
    QVERIFY(!w.exportServer());
    QVERIFY(!QFile::exists(path));
}

void McpExportClaudeCodeTest::shouldExportSseServer()
{
    QTemporaryDir dir;
    QVERIFY(dir.isValid());
    const QString path = dir.filePath(u".mcp.json"_s);

    McpProtocolSettings settings;
    settings.setServerUrl(QUrl(u"https://example.com/sse"_s));
    McpExportClaudeCode w;
    w.setServer(createServer(u"legacy"_s, McpProtocolPlugin::TransportType::Sse, settings));
    w.setPath(path);
    QVERIFY(w.exportServer());

    const QJsonObject server = readJson(path).value("mcpServers"_L1).toObject().value("legacy"_L1).toObject();
    QCOMPARE(server.value("type"_L1).toString(), u"sse"_s);
    QCOMPARE(server.value("url"_L1).toString(), u"https://example.com/sse"_s);
    QVERIFY(!server.contains("headers"_L1));
    QVERIFY(!server.contains("command"_L1));
}

void McpExportClaudeCodeTest::shouldExportStreamableHttpServer()
{
    QTemporaryDir dir;
    QVERIFY(dir.isValid());
    const QString path = dir.filePath(u".mcp.json"_s);

    McpProtocolSettings settings;
    settings.setServerUrl(QUrl(u"https://example.com/mcp"_s));
    settings.setHeaders({u"X-Api-Key: abc"_s, u"invalid-header"_s, u"X-Url: http://foo"_s});
    McpExportClaudeCode w;
    w.setServer(createServer(u"remote"_s, McpProtocolPlugin::TransportType::StreamableHttp, settings));
    w.setPath(path);
    QVERIFY(w.exportServer());

    const QJsonObject server = readJson(path).value("mcpServers"_L1).toObject().value("remote"_L1).toObject();
    QCOMPARE(server.value("type"_L1).toString(), u"http"_s);
    QCOMPARE(server.value("url"_L1).toString(), u"https://example.com/mcp"_s);
    // Invalid header is skipped, value can contain ':'
    const QJsonObject expectedHeaders{{u"X-Api-Key"_s, u"abc"_s}, {u"X-Url"_s, u"http://foo"_s}};
    QCOMPARE(server.value("headers"_L1).toObject(), expectedHeaders);
}

void McpExportClaudeCodeTest::shouldNotExportAuthToken()
{
    QTemporaryDir dir;
    QVERIFY(dir.isValid());
    const QString path = dir.filePath(u".mcp.json"_s);

    const QByteArray secret = "my-secret-token"_ba;
    McpProtocolSettings settings;
    settings.setServerUrl(QUrl(u"https://example.com/mcp"_s));
    settings.setAuthToken(secret);
    McpExportClaudeCode w;
    w.setServer(createServer(u"remote"_s, McpProtocolPlugin::TransportType::StreamableHttp, settings));
    w.setPath(path);
    QVERIFY(w.exportServer());

    QFile file(path);
    QVERIFY(file.open(QIODevice::ReadOnly));
    QVERIFY(!file.readAll().contains(secret));

    const QJsonObject server = readJson(path).value("mcpServers"_L1).toObject().value("remote"_L1).toObject();
    QCOMPARE(server.value("headers"_L1).toObject().value("Authorization"_L1).toString(), u"Bearer ${MCP_AUTH_TOKEN}"_s);
}

void McpExportClaudeCodeTest::shouldMergeWithExistingFile()
{
    QTemporaryDir dir;
    QVERIFY(dir.isValid());
    const QString path = dir.filePath(u".mcp.json"_s);
    writeFile(path, R"({"otherSetting": 42, "mcpServers": {"existing": {"type": "sse", "url": "https://foo.org"}}})");

    McpExportClaudeCode w;
    w.setServer(createStdioServer());
    w.setPath(path);
    QVERIFY(w.exportServer());

    const QJsonObject root = readJson(path);
    QCOMPARE(root.value("otherSetting"_L1).toInt(), 42);
    const QJsonObject mcpServers = root.value("mcpServers"_L1).toObject();
    QCOMPARE(mcpServers.count(), 2);
    QCOMPARE(mcpServers.value("existing"_L1).toObject().value("url"_L1).toString(), u"https://foo.org"_s);
    QCOMPARE(mcpServers.value("git"_L1).toObject().value("type"_L1).toString(), u"stdio"_s);

    // Exporting the same server again replaces it
    QVERIFY(w.exportServer());
    QCOMPARE(readJson(path).value("mcpServers"_L1).toObject().count(), 2);
}

void McpExportClaudeCodeTest::shouldNotOverwriteInvalidJsonFile()
{
    QTemporaryDir dir;
    QVERIFY(dir.isValid());
    const QString path = dir.filePath(u".mcp.json"_s);
    const QByteArray invalidJson = "{ not json";
    writeFile(path, invalidJson);

    McpExportClaudeCode w;
    w.setServer(createStdioServer());
    w.setPath(path);
    QVERIFY(!w.exportServer());

    QFile file(path);
    QVERIFY(file.open(QIODevice::ReadOnly));
    QCOMPARE(file.readAll(), invalidJson);
}

#include "moc_mcpexportclaudecodetest.cpp"
