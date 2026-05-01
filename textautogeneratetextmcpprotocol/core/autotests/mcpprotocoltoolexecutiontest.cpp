/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoltoolexecutiontest.h"
#include "impl/mcpprotocoltoolexecution.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolToolExecutionTest)

McpProtocolToolExecutionTest::McpProtocolToolExecutionTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolToolExecutionTest::shouldhaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolToolExecution w;
    QVERIFY(!w.taskSupport().has_value());
}

#include "moc_mcpprotocoltoolexecutiontest.cpp"
