/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolnotificationparamstest.h"
#include "impl/mcpprotocolnotificationparams.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolNotificationParamsTest)

McpProtocolNotificationParamsTest::McpProtocolNotificationParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolNotificationParamsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolNotificationParams w;
    QVERIFY(!w.meta().has_value());
}
#include "moc_mcpprotocolnotificationparamstest.cpp"
