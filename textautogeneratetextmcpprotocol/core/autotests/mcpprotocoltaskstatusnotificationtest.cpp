/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoltaskstatusnotificationtest.h"
#include "impl/mcpprotocoltaskstatusnotification.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolTaskStatusNotificationTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolTaskStatusNotificationTest::McpProtocolTaskStatusNotificationTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolTaskStatusNotificationTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolTaskStatusNotification w;
    QCOMPARE(w.type(), "notifications/tasks/status"_ba);
}
#include "moc_mcpprotocoltaskstatusnotificationtest.cpp"
