/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolinitializednotificationtest.h"
#include "mcpprotocolinitializednotification.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolInitializedNotificationTest)

McpProtocolInitializedNotificationTest::McpProtocolInitializedNotificationTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolInitializedNotificationTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializedNotification w;
    QVERIFY(!w.params().has_value());
}
#include "moc_mcpprotocolinitializednotificationtest.cpp"
