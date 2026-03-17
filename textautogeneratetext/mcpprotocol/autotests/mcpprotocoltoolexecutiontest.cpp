/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoltoolexecutiontest.h"
#include "mcpprotocoltoolexecution.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolToolExecutionTest)

McpProtocolToolExecutionTest::McpProtocolToolExecutionTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolToolExecutionTest::shouldhaveDefaultValues()
{
    const McpProtocol::McpProtocolToolExecution w;
    QCOMPARE(w.taskSupport(), McpProtocol::McpProtocolToolExecution::TaskSupport::Unknown);
}

#include "moc_mcpprotocoltoolexecutiontest.cpp"
