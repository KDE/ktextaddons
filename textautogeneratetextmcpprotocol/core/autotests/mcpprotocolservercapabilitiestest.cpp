/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolservercapabilitiestest.h"
#include "impl/mcpprotocolservercapabilities.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolServerCapabilitiesTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolServerCapabilitiesTest::McpProtocolServerCapabilitiesTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolServerCapabilitiesTest::shouldHaveDefaultValues()
{
    const McpProtocolServerCapabilities w;
    QVERIFY(!w.completions().has_value());
    QVERIFY(!w.experimental().has_value());
    QVERIFY(!w.logging().has_value());
    QVERIFY(!w.prompts().has_value());
    QVERIFY(!w.resources().has_value());
    QVERIFY(!w.tasks().has_value());
    QVERIFY(!w.tools().has_value());
    QCOMPARE(McpProtocolServerCapabilities::toJson(w), QJsonObject{});
}

void McpProtocolServerCapabilitiesTest::shouldConvertJson()
{
    QJsonObject prompts;
    prompts["listChanged"_L1] = true;
    QJsonObject resources;
    resources["listChanged"_L1] = false;
    resources["subscribe"_L1] = true;
    QJsonObject tools;
    tools["listChanged"_L1] = true;
    QJsonObject taskCall;
    taskCall["ttl"_L1] = 42;
    QJsonObject taskTools;
    taskTools["call"_L1] = taskCall;
    QJsonObject taskRequests;
    taskRequests["tools"_L1] = taskTools;
    QJsonObject tasks;
    tasks["cancel"_L1] = QJsonObject{};
    tasks["list"_L1] = QJsonObject{};
    tasks["requests"_L1] = taskRequests;
    QJsonObject experimentalEntry;
    experimentalEntry["enabled"_L1] = true;
    QJsonObject experimental;
    experimental["myFeature"_L1] = experimentalEntry;

    QJsonObject obj;
    obj["completions"_L1] = QJsonObject{};
    obj["experimental"_L1] = experimental;
    obj["logging"_L1] = QJsonObject{};
    obj["prompts"_L1] = prompts;
    obj["resources"_L1] = resources;
    obj["tasks"_L1] = tasks;
    obj["tools"_L1] = tools;

    const auto capabilities = McpProtocolServerCapabilities::fromJson(obj);
    QVERIFY(capabilities.completions().has_value());
    QVERIFY(capabilities.logging().has_value());
    QVERIFY(capabilities.prompts().has_value());
    QCOMPARE(capabilities.prompts()->listChanged(), true);
    QVERIFY(capabilities.resources().has_value());
    QCOMPARE(capabilities.resources()->listChanged(), false);
    QCOMPARE(capabilities.resources()->subscribe(), true);
    QVERIFY(capabilities.tools().has_value());
    QCOMPARE(capabilities.tools()->listChanged(), true);
    QVERIFY(capabilities.experimental().has_value());
    QCOMPARE(capabilities.experimental()->value(u"myFeature"_s), experimentalEntry);
    QVERIFY(capabilities.tasks().has_value());
    QVERIFY(capabilities.tasks()->cancel().has_value());
    QVERIFY(capabilities.tasks()->list().has_value());
    QVERIFY(capabilities.tasks()->requests().has_value());
    QVERIFY(capabilities.tasks()->requests()->tools().has_value());
    QCOMPARE(capabilities.tasks()->requests()->tools()->call()->value(u"ttl"_s).toInt(), 42);

    QCOMPARE(McpProtocolServerCapabilities::toJson(capabilities), obj);
}

#include "moc_mcpprotocolservercapabilitiestest.cpp"
