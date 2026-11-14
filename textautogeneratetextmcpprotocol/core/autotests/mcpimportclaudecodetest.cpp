/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpimportclaudecodetest.h"
#include "importexport/mcpexportclaudecode.h"
#include "importexport/mcpimportclaudecode.h"

#include <QFile>
#include <QTemporaryDir>
#include <QTest>

QTEST_GUILESS_MAIN(McpImportClaudeCodeTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;

namespace
{
void writeFile(const QString &path, const QByteArray &data)
{
    QFile file(path);
    QVERIFY(file.open(QIODevice::WriteOnly));
    file.write(data);
}

McpServer findServer(const QList<McpServer> &servers, const QString &name)
{
    for (const McpServer &server : servers) {
        if (server.name() == name) {
            return server;
        }
    }
    return {};
}
}

McpImportClaudeCodeTest::McpImportClaudeCodeTest(QObject *parent)
    : QObject{parent}
{
}

void McpImportClaudeCodeTest::shouldHaveDefaultValues()
{
    McpImportClaudeCode w;
    QVERIFY(w.path().isEmpty());
    QVERIFY(w.mcpServers().isEmpty());
    QVERIFY(!w.importServer());
}

void McpImportClaudeCodeTest::shouldNotImportMissingFile()
{
    QTemporaryDir dir;
    QVERIFY(dir.isValid());
    McpImportClaudeCode w;
    w.setPath(dir.filePath(u"missing.json"_s));
    QVERIFY(!w.importServer());
    QVERIFY(w.mcpServers().isEmpty());
}

void McpImportClaudeCodeTest::shouldNotImportInvalidJson()
{
    QTemporaryDir dir;
    QVERIFY(dir.isValid());
    const QString path = dir.filePath(u".mcp.json"_s);
    writeFile(path, "{ not json");
    McpImportClaudeCode w;
    w.setPath(path);
    QVERIFY(!w.importServer());
    QVERIFY(w.mcpServers().isEmpty());
}

void McpImportClaudeCodeTest::shouldNotImportFileWithoutServers()
{
    QTemporaryDir dir;
    QVERIFY(dir.isValid());
    const QString path = dir.filePath(u".mcp.json"_s);
    writeFile(path, R"({"other": 1})");
    McpImportClaudeCode w;
    w.setPath(path);
    QVERIFY(!w.importServer());
    QVERIFY(w.mcpServers().isEmpty());
}

void McpImportClaudeCodeTest::shouldImportStdioServer()
{
    QTemporaryDir dir;
    QVERIFY(dir.isValid());
    const QString path = dir.filePath(u".mcp.json"_s);
    // No "type": stdio by default
    writeFile(path, R"({"mcpServers": {"git": {"command": "uvx", "args": ["mcp-server-git", "--repository", "/tmp/my repo"], "env": {"FOO": "bar"}}}})");

    McpImportClaudeCode w;
    w.setPath(path);
    QVERIFY(w.importServer());
    QCOMPARE(w.mcpServers().count(), 1);
    const McpServer server = w.mcpServers().constFirst();
    QCOMPARE(server.name(), u"git"_s);
    QVERIFY(!server.identifier().isEmpty());
    QCOMPARE(server.transportType(), McpProtocolPlugin::TransportType::Stdio);
    QCOMPARE(server.settings().command(), u"uvx"_s);
    QCOMPARE(server.settings().arguments(), u"mcp-server-git --repository '/tmp/my repo'"_s);
    const QMap<QString, QString> expectedEnv{{u"FOO"_s, u"bar"_s}};
    QCOMPARE(server.settings().environments(), expectedEnv);
}

void McpImportClaudeCodeTest::shouldImportUrlServers()
{
    QTemporaryDir dir;
    QVERIFY(dir.isValid());
    const QString path = dir.filePath(u".mcp.json"_s);
    writeFile(path, R"({"mcpServers": {
        "sse": {"type": "sse", "url": "https://example.com/sse", "headers": {"Authorization": "Bearer ${MCP_AUTH_TOKEN}", "X-Api": "foo"}},
        "http": {"type": "http", "url": "https://example.com/mcp", "headers": {"Authorization": "Bearer secret"}},
        "nottype": {"url": "https://example.com/other"}
    }})");

    McpImportClaudeCode w;
    w.setPath(path);
    QVERIFY(w.importServer());
    const QList<McpServer> servers = w.mcpServers();
    QCOMPARE(servers.count(), 3);

    const McpServer sse = findServer(servers, u"sse"_s);
    QCOMPARE(sse.transportType(), McpProtocolPlugin::TransportType::Sse);
    QCOMPARE(sse.settings().serverUrl(), QUrl(u"https://example.com/sse"_s));
    QCOMPARE(sse.settings().headers(), QStringList{u"X-Api: foo"_s});
    // Environment variable can't be used as token
    QVERIFY(sse.settings().authToken().isEmpty());

    const McpServer http = findServer(servers, u"http"_s);
    QCOMPARE(http.transportType(), McpProtocolPlugin::TransportType::StreamableHttp);
    QCOMPARE(http.settings().serverUrl(), QUrl(u"https://example.com/mcp"_s));
    QVERIFY(http.settings().headers().isEmpty());
    QCOMPARE(http.settings().authToken(), QByteArray("secret"));

    const McpServer noType = findServer(servers, u"nottype"_s);
    QCOMPARE(noType.transportType(), McpProtocolPlugin::TransportType::StreamableHttp);
}

void McpImportClaudeCodeTest::shouldSkipInvalidServers()
{
    QTemporaryDir dir;
    QVERIFY(dir.isValid());
    const QString path = dir.filePath(u".mcp.json"_s);
    writeFile(path, R"({"mcpServers": {
        "nocommand": {"type": "stdio"},
        "unknown": {"type": "websocket", "url": "wss://example.com"},
        "valid": {"command": "foo"}
    }})");

    McpImportClaudeCode w;
    w.setPath(path);
    QVERIFY(w.importServer());
    QCOMPARE(w.mcpServers().count(), 1);
    QCOMPARE(w.mcpServers().constFirst().name(), u"valid"_s);
}

void McpImportClaudeCodeTest::shouldImportExportedServer()
{
    QTemporaryDir dir;
    QVERIFY(dir.isValid());
    const QString path = dir.filePath(u".mcp.json"_s);

    McpProtocolSettings settings;
    settings.setCommand(u"uvx"_s);
    settings.setArguments(u"mcp-server-git --repository '/tmp/my repo'"_s);
    settings.setEnvironments({{u"FOO"_s, u"bar"_s}});
    McpServer server;
    server.setName(u"git"_s);
    server.createUniqueIdentifier();
    server.setTransportType(McpProtocolPlugin::TransportType::Stdio);
    server.setSettings(settings);

    McpExportClaudeCode exporter;
    exporter.setServer(server);
    exporter.setPath(path);
    QVERIFY(exporter.exportServer());

    McpImportClaudeCode w;
    w.setPath(path);
    QVERIFY(w.importServer());
    QCOMPARE(w.mcpServers().count(), 1);
    const McpServer imported = w.mcpServers().constFirst();
    QCOMPARE(imported.name(), server.name());
    QCOMPARE(imported.transportType(), server.transportType());
    QCOMPARE(imported.settings().command(), settings.command());
    QCOMPARE(imported.settings().arguments(), settings.arguments());
    QCOMPARE(imported.settings().environments(), settings.environments());
}

#include "moc_mcpimportclaudecodetest.cpp"
