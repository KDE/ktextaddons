/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolmodelpreferencestest.h"
#include "mcpprotocolmodelpreferences.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolModelPreferencesTest)

McpProtocolModelPreferencesTest::McpProtocolModelPreferencesTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolModelPreferencesTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolModelPreferences w;
    QVERIFY(!w.costPriority().has_value());
    QVERIFY(!w.hints().has_value());
    QVERIFY(!w.intelligencePriority().has_value());
    QVERIFY(!w.speedPriority().has_value());
}
#include "moc_mcpprotocolmodelpreferencestest.cpp"
