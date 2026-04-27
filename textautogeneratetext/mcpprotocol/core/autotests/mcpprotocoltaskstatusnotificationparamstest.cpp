/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoltaskstatusnotificationparamstest.h"
#include "mcpprotocoltaskstatusnotificationparams.h"
#include <QTest>
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
#include "moc_mcpprotocoltaskstatusnotificationparamstest.cpp"
