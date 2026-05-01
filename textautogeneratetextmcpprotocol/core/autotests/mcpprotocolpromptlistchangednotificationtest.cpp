/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolpromptlistchangednotificationtest.h"
#include "impl/mcpprotocolpromptlistchangednotification.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolPromptListChangedNotificationTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolPromptListChangedNotificationTest::McpProtocolPromptListChangedNotificationTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolPromptListChangedNotificationTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolPromptListChangedNotification w;
    QVERIFY(!w.params().has_value());
    QCOMPARE(w.type(), "notifications/prompts/list_changed"_ba);
}
#include "moc_mcpprotocolpromptlistchangednotificationtest.cpp"
