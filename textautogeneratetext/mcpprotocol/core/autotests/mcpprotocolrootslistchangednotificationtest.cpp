/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolrootslistchangednotificationtest.h"
#include "mcpprotocolrootslistchangednotification.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolRootsListChangedNotificationTest)

McpProtocolRootsListChangedNotificationTest::McpProtocolRootsListChangedNotificationTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolRootsListChangedNotificationTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolRootsListChangedNotification w;
    QVERIFY(!w.params().has_value());
}
#include "moc_mcpprotocolrootslistchangednotificationtest.cpp"
