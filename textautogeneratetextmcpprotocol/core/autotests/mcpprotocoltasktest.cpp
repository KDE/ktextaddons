/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoltasktest.h"
#include "impl/mcpprotocoltask.h"
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolTaskTest)

McpProtocolTaskTest::McpProtocolTaskTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolTaskTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolTask w;
    QVERIFY(w.createdAt().isEmpty());
    QVERIFY(w.lastUpdatedAt().isEmpty());
    QVERIFY(w.taskId().isEmpty());
    QVERIFY(!w.pollInterval().has_value());
    QVERIFY(!w.statusMessage().has_value());
    QVERIFY(!w.ttl().has_value());
    QCOMPARE(w.status(), TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::TaskStatus::Unknown);
}

void McpProtocolTaskTest::shouldLoadAndSaveTtl()
{
    QJsonObject obj;
    obj["taskId"_L1] = u"t1"_s;
    obj["status"_L1] = u"working"_s;
    obj["createdAt"_L1] = u"2025-11-25T10:00:00Z"_s;
    obj["lastUpdatedAt"_L1] = u"2025-11-25T10:00:01Z"_s;

    const auto withoutTtl = TextAutoGenerateTextMcpProtocolCore::McpProtocolTask::fromJson(obj);
    QVERIFY(!withoutTtl.ttl().has_value());

    obj["ttl"_L1] = QJsonValue::Null;
    const auto nullTtl = TextAutoGenerateTextMcpProtocolCore::McpProtocolTask::fromJson(obj);
    QVERIFY(!nullTtl.ttl().has_value());
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolTask::toJson(nullTtl), obj);

    obj["ttl"_L1] = 60000;
    const auto task = TextAutoGenerateTextMcpProtocolCore::McpProtocolTask::fromJson(obj);
    QCOMPARE(*task.ttl(), qint64(60000));
    QCOMPARE(task.status(), TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::TaskStatus::Working);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolTask::toJson(task), obj);
}

#include "moc_mcpprotocoltasktest.cpp"
