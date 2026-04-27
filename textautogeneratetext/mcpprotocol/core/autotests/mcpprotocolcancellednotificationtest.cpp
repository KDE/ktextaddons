/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolcancellednotificationtest.h"
#include "mcpprotocolcancellednotification.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolCancelledNotificationTest)

McpProtocolCancelledNotificationTest::McpProtocolCancelledNotificationTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolCancelledNotificationTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolCancelledNotification w;
    // TODO
}
#include "moc_mcpprotocolcancellednotificationtest.cpp"
