/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolresulttest.h"
#include "impl/mcpprotocolresult.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolResultTest)

McpProtocolResultTest::McpProtocolResultTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolResultTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolResult w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(w.additionalProperties().isEmpty());
}
#include "moc_mcpprotocolresulttest.cpp"
