/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolresourcelistchangednotificationtest.h"
#include "mcpprotocolresourcelistchangednotification.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolResourceListChangedNotificationTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolResourceListChangedNotificationTest::McpProtocolResourceListChangedNotificationTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolResourceListChangedNotificationTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceListChangedNotification w;
    QVERIFY(!w.params().has_value());
    QCOMPARE(w.type(), "notifications/resources/list_changed"_ba);
}
#include "moc_mcpprotocolresourcelistchangednotificationtest.cpp"
