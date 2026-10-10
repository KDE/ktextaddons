/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolsettingstest.h"
#include "common/mcpprotocolsettings.h"
#include <KConfig>
#include <KConfigGroup>
#include <QStandardPaths>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolSettingsTest)

McpProtocolSettingsTest::McpProtocolSettingsTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void McpProtocolSettingsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings w;
    QVERIFY(w.command().isEmpty());
    QVERIFY(w.arguments().isEmpty());
    QVERIFY(w.environments().isEmpty());
    QVERIFY(w.serverUrl().isEmpty());
    QVERIFY(w.headers().isEmpty());
    QVERIFY(w.roots().isEmpty());
}

void McpProtocolSettingsTest::shouldLoadSaveSettings()
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setCommand(u"command"_s);
    settings.setHeaders({u"Authorization: Bearer foo"_s});
    settings.setRoots({u"/home/user/project"_s, u"/tmp"_s});
    // In-memory config
    KConfig config(QString(), KConfig::SimpleConfig);
    KConfigGroup group = config.group(u"Server"_s);
    settings.save(group);

    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings loaded;
    loaded.load(group);
    QCOMPARE(loaded, settings);
    QCOMPARE(loaded.roots(), QStringList({u"/home/user/project"_s, u"/tmp"_s}));
}

#include "moc_mcpprotocolsettingstest.cpp"
