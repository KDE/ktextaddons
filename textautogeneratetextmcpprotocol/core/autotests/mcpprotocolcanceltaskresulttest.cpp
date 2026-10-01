/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolcanceltaskresulttest.h"
#include "impl/mcpprotocolcanceltaskresult.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolCancelTaskResultTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolCancelTaskResultTest::McpProtocolCancelTaskResultTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolCancelTaskResultTest::shouldHaveDefaultValues()
{
    const McpProtocolCancelTaskResult w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(w.createdAt().isEmpty());
    QVERIFY(w.lastUpdatedAt().isEmpty());
    QVERIFY(!w.pollInterval().has_value());
    QCOMPARE(w.status(), McpProtocolUtils::TaskStatus::Unknown);
    QVERIFY(!w.statusMessage().has_value());
    QVERIFY(w.taskId().isEmpty());
    QVERIFY(!w.ttl().has_value());
    QCOMPARE(w, McpProtocolCancelTaskResult());
}

void McpProtocolCancelTaskResultTest::shouldConvertJson()
{
    QJsonObject obj;
    obj["createdAt"_L1] = u"2025-11-25T10:30:00Z"_s;
    obj["lastUpdatedAt"_L1] = u"2025-11-25T10:31:00Z"_s;
    obj["status"_L1] = u"working"_s;
    obj["taskId"_L1] = u"task-1"_s;
    obj["pollInterval"_L1] = 5000;
    obj["ttl"_L1] = qint64(3000000000);

    const McpProtocolCancelTaskResult result = McpProtocolCancelTaskResult::fromJson(obj);
    QCOMPARE(result.createdAt(), u"2025-11-25T10:30:00Z"_s);
    QCOMPARE(result.lastUpdatedAt(), u"2025-11-25T10:31:00Z"_s);
    QCOMPARE(result.status(), McpProtocolUtils::TaskStatus::Working);
    QCOMPARE(result.taskId(), u"task-1"_s);
    QVERIFY(result.pollInterval().has_value());
    QCOMPARE(*result.pollInterval(), qint64(5000));
    QVERIFY(result.ttl().has_value());
    QCOMPARE(*result.ttl(), qint64(3000000000));

    const QJsonObject json = McpProtocolCancelTaskResult::toJson(result);
    QCOMPARE(json.value("pollInterval"_L1).toInteger(), qint64(5000));
    QCOMPARE(json.value("ttl"_L1).toInteger(), qint64(3000000000));
    QCOMPARE(json, obj);
    QCOMPARE(McpProtocolCancelTaskResult::fromJson(json), result);

    obj["ttl"_L1] = QJsonValue::Null;
    obj.remove("pollInterval"_L1);
    const McpProtocolCancelTaskResult nullTtl = McpProtocolCancelTaskResult::fromJson(obj);
    QVERIFY(!nullTtl.ttl().has_value());
    QVERIFY(!nullTtl.pollInterval().has_value());
    QCOMPARE(McpProtocolCancelTaskResult::toJson(nullTtl), obj);
}

#include "moc_mcpprotocolcanceltaskresulttest.cpp"
