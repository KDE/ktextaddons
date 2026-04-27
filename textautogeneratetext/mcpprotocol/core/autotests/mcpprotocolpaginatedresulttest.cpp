/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolpaginatedresulttest.h"
#include "mcpprotocolpaginatedresult.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolPaginatedResultTest)

McpProtocolPaginatedResultTest::McpProtocolPaginatedResultTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolPaginatedResultTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolPaginatedResult w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.nextCursor().has_value());
}
#include "moc_mcpprotocolpaginatedresulttest.cpp"
