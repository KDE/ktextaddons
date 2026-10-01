/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolinitializednotificationtest.h"
#include "impl/mcpprotocolinitializednotification.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolInitializedNotificationTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;

McpProtocolInitializedNotificationTest::McpProtocolInitializedNotificationTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolInitializedNotificationTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializedNotification w;
    QVERIFY(!w.params().has_value());
    QCOMPARE(McpProtocolInitializedNotification::type(), "notifications/initialized"_ba);
}
void McpProtocolInitializedNotificationTest::shouldConvertJson()
{
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = u"notifications/initialized"_s;
    obj["params"_L1] = QJsonObject();

    const McpProtocolInitializedNotification notification = McpProtocolInitializedNotification::fromJson(obj);
    QVERIFY(notification.params().has_value());
    QCOMPARE(McpProtocolInitializedNotification::toJson(notification), obj);

    QJsonObject withoutParams;
    withoutParams["jsonrpc"_L1] = u"2.0"_s;
    withoutParams["method"_L1] = u"notifications/initialized"_s;
    QCOMPARE(McpProtocolInitializedNotification::toJson(McpProtocolInitializedNotification::fromJson(withoutParams)), withoutParams);

    QJsonObject wrongMethod = obj;
    wrongMethod["method"_L1] = u"notifications/cancelled"_s;
    QVERIFY(!McpProtocolInitializedNotification::fromJson(wrongMethod).params().has_value());
}

#include "moc_mcpprotocolinitializednotificationtest.cpp"
