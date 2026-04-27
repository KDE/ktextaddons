/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoltoolchoicetest.h"
#include "mcpprotocoltoolchoice.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolToolChoiceTest)

McpProtocolToolChoiceTest::McpProtocolToolChoiceTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolToolChoiceTest::shouldhaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolToolChoice w;
    QCOMPARE(w.mode(), TextAutoGenerateTextMcpProtocolCore::McpProtocolToolChoice::Mode::Unknown);
}

#include "moc_mcpprotocoltoolchoicetest.cpp"
