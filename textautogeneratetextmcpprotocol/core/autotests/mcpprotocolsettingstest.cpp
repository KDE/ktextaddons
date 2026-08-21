/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolsettingstest.h"
#include "common/mcpprotocolsettings.h"
#include <QStandardPaths>
#include <QTest>
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
}

#include "moc_mcpprotocolsettingstest.cpp"
