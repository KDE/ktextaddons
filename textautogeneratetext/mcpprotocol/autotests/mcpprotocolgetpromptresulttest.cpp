/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolgetpromptresulttest.h"
#include "mcpprotocolgetpromptresult.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolGetPromptResultTest)

McpProtocolGetPromptResultTest::McpProtocolGetPromptResultTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolGetPromptResultTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolGetPromptResult w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.description().has_value());
}
#include "moc_mcpprotocolgetpromptresulttest.cpp"
