/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpregistryserverinfotest.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QTest>
#include <TextAutoGenerateTextMcpProtocolCore/McpRegistryServerInfo>
QTEST_GUILESS_MAIN(McpRegistryServerInfoTest)

using namespace Qt::Literals::StringLiterals;
McpRegistryServerInfoTest::McpRegistryServerInfoTest(QObject *parent)
    : QObject{parent}
{
}

void McpRegistryServerInfoTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpRegistryServerInfo info;
    QVERIFY(!info.isValid());
    QVERIFY(info.name().isEmpty());
    QVERIFY(info.title().isEmpty());
    QVERIFY(info.displayName().isEmpty());
    QVERIFY(info.description().isEmpty());
    QVERIFY(info.version().isEmpty());
    QVERIFY(info.repositoryUrl().isEmpty());
    QVERIFY(info.websiteUrl().isEmpty());
    QVERIFY(info.packages().isEmpty());
    QVERIFY(info.remotes().isEmpty());
    QVERIFY(info.icons().isEmpty());
}

void McpRegistryServerInfoTest::shouldParseServerList()
{
    const QByteArray json = R"({
  "servers": [
    {
      "server": {
        "name": "io.github.foo/bar",
        "title": "Bar",
        "description": "Bar server",
        "version": "1.2.3",
        "repository": {"url": "https://github.com/foo/bar", "source": "github"},
        "websiteUrl": "https://bar.example.com",
        "packages": [
          {
            "registryType": "npm",
            "identifier": "@foo/bar",
            "version": "1.2.3",
            "runtimeHint": "npx",
            "transport": {"type": "stdio"},
            "environmentVariables": [
              {"name": "TOKEN", "description": "Api token", "isRequired": true, "isSecret": true},
              {"name": "ROOT"}
            ]
          }
        ],
        "remotes": [{"type": "streamable-http", "url": "https://bar.example.com/mcp"}]
      },
      "_meta": {}
    },
    {
      "server": {"name": "io.github.foo/baz", "version": "0.1.0"}
    },
    {
      "server": {"description": "invalid, no name"}
    }
  ],
  "metadata": {"nextCursor": "io.github.foo/baz:0.1.0", "count": 3}
})";
    const QJsonObject obj = QJsonDocument::fromJson(json).object();
    QString nextCursor;
    const auto list = TextAutoGenerateTextMcpProtocolCore::McpRegistryServerInfo::parseServerList(obj, nextCursor);
    QCOMPARE(nextCursor, u"io.github.foo/baz:0.1.0"_s);
    QCOMPARE(list.count(), 2);

    const auto &first = list.at(0);
    QCOMPARE(first.name(), u"io.github.foo/bar"_s);
    QCOMPARE(first.displayName(), u"Bar"_s);
    QCOMPARE(first.description(), u"Bar server"_s);
    QCOMPARE(first.version(), u"1.2.3"_s);
    QCOMPARE(first.repositoryUrl(), u"https://github.com/foo/bar"_s);
    QCOMPARE(first.websiteUrl(), u"https://bar.example.com"_s);
    QCOMPARE(first.packages().count(), 1);
    const auto package = first.packages().constFirst();
    QCOMPARE(package.registryType, u"npm"_s);
    QCOMPARE(package.identifier, u"@foo/bar"_s);
    QCOMPARE(package.runtimeHint, u"npx"_s);
    QCOMPARE(package.transportType, u"stdio"_s);
    QCOMPARE(package.environmentVariables.count(), 2);
    QVERIFY(package.environmentVariables.at(0).isRequired);
    QVERIFY(package.environmentVariables.at(0).isSecret);
    QVERIFY(!package.environmentVariables.at(1).isRequired);
    QCOMPARE(first.remotes().count(), 1);
    QCOMPARE(first.remotes().constFirst().type, u"streamable-http"_s);
    QCOMPARE(first.remotes().constFirst().url, u"https://bar.example.com/mcp"_s);

    const auto &second = list.at(1);
    QCOMPARE(second.displayName(), u"io.github.foo/baz"_s);
    QVERIFY(second.packages().isEmpty());
    QVERIFY(second.remotes().isEmpty());
    QVERIFY(second.icons().isEmpty());
}

void McpRegistryServerInfoTest::shouldParseIcons()
{
    const QByteArray json = R"({
  "name": "io.github.foo/bar",
  "icons": [
    {"src": "https://bar.example.com/icon.png", "mimeType": "image/png", "sizes": ["48x48"]},
    {"src": "https://bar.example.com/icon.svg"},
    {"mimeType": "image/png"}
  ]
})";
    const QJsonObject obj = QJsonDocument::fromJson(json).object();
    const auto info = TextAutoGenerateTextMcpProtocolCore::McpRegistryServerInfo::fromJson(obj);
    QVERIFY(info.isValid());
    const auto icons = info.icons();
    QCOMPARE(icons.count(), 2);
    QCOMPARE(icons.at(0).url, u"https://bar.example.com/icon.png"_s);
    QCOMPARE(icons.at(0).mimetype, u"image/png"_s);
    QCOMPARE(icons.at(1).url, u"https://bar.example.com/icon.svg"_s);
    QVERIFY(icons.at(1).mimetype.isEmpty());
}
#include "moc_mcpregistryserverinfotest.cpp"
