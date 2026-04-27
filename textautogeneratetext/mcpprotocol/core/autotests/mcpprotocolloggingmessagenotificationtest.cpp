/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolloggingmessagenotificationtest.h"
#include "mcpprotocolloggingmessagenotification.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolLoggingMessageNotificationTest)

McpProtocolLoggingMessageNotificationTest::McpProtocolLoggingMessageNotificationTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolLoggingMessageNotificationTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolLoggingMessageNotification w;
    // TODO
}
#include "moc_mcpprotocolloggingmessagenotificationtest.cpp"
