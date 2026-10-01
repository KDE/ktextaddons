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
    QVERIFY(!TextAutoGenerateTextMcpProtocolCore::McpProtocolTaskStatusNotificationParams::fromJson(obj).ttl().has_value());
    obj["ttl"_L1] = 1000;
    QCOMPARE(*TextAutoGenerateTextMcpProtocolCore::McpProtocolTaskStatusNotificationParams::fromJson(obj).ttl(), qint64(1000));
}

#include "moc_mcpprotocoltaskstatusnotificationparamstest.cpp"
