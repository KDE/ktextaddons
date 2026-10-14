/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolresourceupdatednotificationtest.h"
#include "impl/mcpprotocolresourceupdatednotification.h"
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolResourceUpdatedNotificationTest)

McpProtocolResourceUpdatedNotificationTest::McpProtocolResourceUpdatedNotificationTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolResourceUpdatedNotificationTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceUpdatedNotification w;
    // QVERIFY(!w.params().has_value());
    QCOMPARE(w.type(), "notifications/resources/updated"_ba);
}

void McpProtocolResourceUpdatedNotificationTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceUpdatedNotification;
    QJsonObject obj{{"jsonrpc"_L1, u"2.0"_s},
                    {"method"_L1, u"notifications/resources/updated"_s},
                    {"params"_L1, QJsonObject{{"uri"_L1, u"file:///foo.txt"_s}}}};
    QCOMPARE(McpProtocolResourceUpdatedNotification::toJson(McpProtocolResourceUpdatedNotification::fromJson(obj)), obj);
    obj["params"_L1] = QJsonObject();
    QCOMPARE(McpProtocolResourceUpdatedNotification::fromJson(obj), McpProtocolResourceUpdatedNotification());
    obj.remove("params"_L1);
    QCOMPARE(McpProtocolResourceUpdatedNotification::fromJson(obj), McpProtocolResourceUpdatedNotification());
}

#include "moc_mcpprotocolresourceupdatednotificationtest.cpp"
