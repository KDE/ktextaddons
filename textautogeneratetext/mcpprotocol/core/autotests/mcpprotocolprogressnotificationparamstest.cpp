/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolprogressnotificationparamstest.h"
#include "mcpprotocolprogressnotificationparams.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolProgressNotificationParamsTest)

McpProtocolProgressNotificationParamsTest::McpProtocolProgressNotificationParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolProgressNotificationParamsTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolProgressNotificationParams w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.message().has_value());
    QVERIFY(!w.total().has_value());
    // QVERIFY(!w.progressToken());
    QCOMPARE(w.progress(), 0.0);
}
#include "moc_mcpprotocolprogressnotificationparamstest.cpp"
