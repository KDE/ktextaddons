/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolelicitationcompletenotificationtest.h"
#include "mcpprotocolelicitationcompletenotification.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolElicitationCompleteNotificationTest)

McpProtocolElicitationCompleteNotificationTest::McpProtocolElicitationCompleteNotificationTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolElicitationCompleteNotificationTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolElicitationCompleteNotification w;
    QVERIFY(w.params().elicitationId().isEmpty());
}
#include "moc_mcpprotocolelicitationcompletenotificationtest.cpp"
