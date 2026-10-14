/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolmodelpreferencestest.h"
#include "impl/mcpprotocolmodelpreferences.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolModelPreferencesTest)
using namespace Qt::Literals::StringLiterals;

McpProtocolModelPreferencesTest::McpProtocolModelPreferencesTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolModelPreferencesTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolModelPreferences w;
    QVERIFY(!w.costPriority().has_value());
    QVERIFY(!w.hints().has_value());
    QVERIFY(!w.intelligencePriority().has_value());
    QVERIFY(!w.speedPriority().has_value());
}

void McpProtocolModelPreferencesTest::shouldIgnoreNonNumericPriority()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolModelPreferences;
    const QJsonObject obj{{"costPriority"_L1, u"high"_s}, {"speedPriority"_L1, 0.5}};
    const McpProtocolModelPreferences prefs = McpProtocolModelPreferences::fromJson(obj);
    QVERIFY(!prefs.costPriority().has_value());
    QVERIFY(!prefs.intelligencePriority().has_value());
    QVERIFY(prefs.speedPriority().has_value());
    QCOMPARE(*prefs.speedPriority(), 0.5);
}

#include "moc_mcpprotocolmodelpreferencestest.cpp"
