/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolresourceupdatednotificationparamstest.h"
#include "mcpprotocolresourceupdatednotificationparams.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolResourceUpdatedNotificationParamsTest)

McpProtocolResourceUpdatedNotificationParamsTest::McpProtocolResourceUpdatedNotificationParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolResourceUpdatedNotificationParamsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceUpdatedNotificationParams w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(w.uri().isEmpty());
}
#include "moc_mcpprotocolresourceupdatednotificationparamstest.cpp"
