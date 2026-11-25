/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolsubscriptionsacknowledgednotificationtest.h"
#include "impl/mcpprotocolsubscriptionsacknowledgednotification.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolSubscriptionsAcknowledgedNotificationTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSubscriptionsAcknowledgedNotificationTest::McpProtocolSubscriptionsAcknowledgedNotificationTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolSubscriptionsAcknowledgedNotificationTest::shouldHaveDefaultValues()
{
    const McpProtocolSubscriptionsAcknowledgedNotification w;
    QCOMPARE(w.type(), "notifications/subscriptions/acknowledged"_ba);
    QVERIFY(!w.params().isValid());
}

void McpProtocolSubscriptionsAcknowledgedNotificationTest::shouldConvertJson()
{
    const QJsonObject obj{{"jsonrpc"_L1, u"2.0"_s},
                          {"method"_L1, u"notifications/subscriptions/acknowledged"_s},
                          {"params"_L1, QJsonObject{{"notifications"_L1, QJsonObject{{"toolsListChanged"_L1, true}}}}}};
    const McpProtocolSubscriptionsAcknowledgedNotification notification = McpProtocolSubscriptionsAcknowledgedNotification::fromJson(obj);
    QVERIFY(notification.params().isValid());
    QCOMPARE(notification.params().notifications()->toolsListChanged(), true);
    QCOMPARE(McpProtocolSubscriptionsAcknowledgedNotification::toJson(notification), obj);
}

void McpProtocolSubscriptionsAcknowledgedNotificationTest::shouldRejectMissingRequiredFields()
{
    QJsonObject obj{{"jsonrpc"_L1, u"2.0"_s},
                    {"method"_L1, u"notifications/subscriptions/acknowledged"_s},
                    {"params"_L1, QJsonObject{{"notifications"_L1, QJsonObject()}}}};
    QCOMPARE(McpProtocolSubscriptionsAcknowledgedNotification::toJson(McpProtocolSubscriptionsAcknowledgedNotification::fromJson(obj)), obj);

    obj["params"_L1] = QJsonObject();
    QCOMPARE(McpProtocolSubscriptionsAcknowledgedNotification::fromJson(obj), McpProtocolSubscriptionsAcknowledgedNotification());
    obj.remove("params"_L1);
    QCOMPARE(McpProtocolSubscriptionsAcknowledgedNotification::fromJson(obj), McpProtocolSubscriptionsAcknowledgedNotification());
    obj["params"_L1] = QJsonObject{{"notifications"_L1, QJsonObject()}};

    obj["method"_L1] = u"notifications/resources/updated"_s;
    QCOMPARE(McpProtocolSubscriptionsAcknowledgedNotification::fromJson(obj), McpProtocolSubscriptionsAcknowledgedNotification());
}

#include "moc_mcpprotocolsubscriptionsacknowledgednotificationtest.cpp"
