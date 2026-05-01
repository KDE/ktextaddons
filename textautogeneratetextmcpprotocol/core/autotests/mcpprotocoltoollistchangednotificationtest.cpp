/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoltoollistchangednotificationtest.h"
#include "impl/mcpprotocoltoollistchangednotification.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolToolListChangedNotificationTest)

McpProtocolToolListChangedNotificationTest::McpProtocolToolListChangedNotificationTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolToolListChangedNotificationTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolToolListChangedNotification w;
    QVERIFY(!w.params().has_value());
}
#include "moc_mcpprotocoltoollistchangednotificationtest.cpp"
