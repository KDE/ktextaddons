/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocollistpromptsresulttest.h"
#include "mcpprotocollistpromptsresult.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolListPromptsResultTest)

McpProtocolListPromptsResultTest::McpProtocolListPromptsResultTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolListPromptsResultTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolListPromptsResult w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.nextCursor().has_value());
    QVERIFY(!w.meta().has_value());
    QVERIFY(w.prompts().isEmpty());
}
#include "moc_mcpprotocollistpromptsresulttest.cpp"
