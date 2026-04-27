/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolcreatetaskresulttest.h"
#include "mcpprotocolcreatetaskresult.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolCreateTaskResultTest)

McpProtocolCreateTaskResultTest::McpProtocolCreateTaskResultTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolCreateTaskResultTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateTaskResult w;
    QVERIFY(!w.meta().has_value());
    // TODO QVERIFY(w.task().isEmpty());
}
#include "moc_mcpprotocolcreatetaskresulttest.cpp"
