/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolresourceupdatednotificationtest.h"
#include "mcpprotocolresourceupdatednotification.h"
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolResourceUpdatedNotificationTest)

McpProtocolResourceUpdatedNotificationTest::McpProtocolResourceUpdatedNotificationTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolResourceUpdatedNotificationTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolResourceUpdatedNotification w;
    // QVERIFY(!w.params().has_value());
    QCOMPARE(w.type(), "notifications/resources/updated"_ba);
}
#include "moc_mcpprotocolresourceupdatednotificationtest.cpp"
