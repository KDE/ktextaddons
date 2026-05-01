/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolprogressnotificationtest.h"
#include "impl/mcpprotocolprogressnotification.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolProgressNotificationTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolProgressNotificationTest::McpProtocolProgressNotificationTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolProgressNotificationTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolProgressNotification w;
    QCOMPARE(w.type(), "notifications/progress"_ba);
    // TODO
}
#include "moc_mcpprotocolprogressnotificationtest.cpp"
