/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoltasktest.h"
#include "mcpprotocoltask.h"
#include <QTest>
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
#include "moc_mcpprotocoltasktest.cpp"
