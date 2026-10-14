/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoltaskstatusnotificationparamstest.h"
#include "impl/mcpprotocoltaskstatusnotificationparams.h"
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolTaskStatusNotificationParamsTest)

McpProtocolTaskStatusNotificationParamsTest::McpProtocolTaskStatusNotificationParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolTaskStatusNotificationParamsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolTaskStatusNotificationParams w;
    QVERIFY(!w.meta().has_value());
    // TODO
}

void McpProtocolTaskStatusNotificationParamsTest::shouldNotSetTtlWhenAbsent()
{
    QJsonObject obj;
    obj["taskId"_L1] = u"t1"_s;
    obj["status"_L1] = u"completed"_s;
    obj["createdAt"_L1] = u"2025-11-25T10:00:00Z"_s;
    obj["lastUpdatedAt"_L1] = u"2025-11-25T10:00:01Z"_s;
    QVERIFY(!TextAutoGenerateTextMcpProtocolCore::McpProtocolTaskStatusNotificationParams::fromJson(obj).ttl().has_value());
    obj["ttl"_L1] = 1000;
    QCOMPARE(*TextAutoGenerateTextMcpProtocolCore::McpProtocolTaskStatusNotificationParams::fromJson(obj).ttl(), qint64(1000));
}

void McpProtocolTaskStatusNotificationParamsTest::shouldRejectMissingRequiredFields()
{
    using namespace TextAutoGenerateTextMcpProtocolCore;
    const QJsonObject obj{{"taskId"_L1, u"t1"_s},
                          {"status"_L1, u"working"_s},
                          {"createdAt"_L1, u"2025-11-25T10:00:00Z"_s},
                          {"lastUpdatedAt"_L1, u"2025-11-25T10:00:01Z"_s}};
    QVERIFY(McpProtocolTaskStatusNotificationParams::fromJson(obj).isValid());
    for (const auto &key : {"taskId"_L1, "status"_L1, "createdAt"_L1, "lastUpdatedAt"_L1}) {
        QJsonObject incomplete = obj;
        incomplete.remove(key);
        QCOMPARE(McpProtocolTaskStatusNotificationParams::fromJson(incomplete), McpProtocolTaskStatusNotificationParams());
    }
    // Unknown status
    QJsonObject unknownStatus = obj;
    unknownStatus["status"_L1] = u"foo"_s;
    QCOMPARE(McpProtocolTaskStatusNotificationParams::fromJson(unknownStatus), McpProtocolTaskStatusNotificationParams());
    // Non numeric ttl is ignored
    QJsonObject invalidTtl = obj;
    invalidTtl["ttl"_L1] = u"foo"_s;
    QVERIFY(!McpProtocolTaskStatusNotificationParams::fromJson(invalidTtl).ttl().has_value());
}

#include "moc_mcpprotocoltaskstatusnotificationparamstest.cpp"
