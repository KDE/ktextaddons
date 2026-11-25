/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolsubscriptionsacknowledgednotificationparamstest.h"
#include "impl/mcpprotocolsubscriptionsacknowledgednotificationparams.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolSubscriptionsAcknowledgedNotificationParamsTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSubscriptionsAcknowledgedNotificationParamsTest::McpProtocolSubscriptionsAcknowledgedNotificationParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolSubscriptionsAcknowledgedNotificationParamsTest::shouldHaveDefaultValues()
{
    const McpProtocolSubscriptionsAcknowledgedNotificationParams w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.notifications().has_value());
    QVERIFY(!w.isValid());
}

void McpProtocolSubscriptionsAcknowledgedNotificationParamsTest::shouldConvertJson()
{
    const QJsonObject obj{{"_meta"_L1, QJsonObject{{"io.modelcontextprotocol/subscriptionId"_L1, 1}}},
                          {"notifications"_L1, QJsonObject{{"promptsListChanged"_L1, true}}}};
    const McpProtocolSubscriptionsAcknowledgedNotificationParams params = McpProtocolSubscriptionsAcknowledgedNotificationParams::fromJson(obj);
    QVERIFY(params.isValid());
    QVERIFY(params.meta().has_value());
    QCOMPARE(params.notifications()->promptsListChanged(), true);
    QCOMPARE(McpProtocolSubscriptionsAcknowledgedNotificationParams::toJson(params), obj);
}

void McpProtocolSubscriptionsAcknowledgedNotificationParamsTest::shouldRejectMissingRequiredFields()
{
    QVERIFY(!McpProtocolSubscriptionsAcknowledgedNotificationParams::fromJson(QJsonObject()).isValid());
    const QJsonObject obj{{"notifications"_L1, u"all"_s}};
    QCOMPARE(McpProtocolSubscriptionsAcknowledgedNotificationParams::fromJson(obj), McpProtocolSubscriptionsAcknowledgedNotificationParams());
}

#include "moc_mcpprotocolsubscriptionsacknowledgednotificationparamstest.cpp"
