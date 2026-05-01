/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocollistresourcetemplatesresulttest.h"
#include "impl/mcpprotocollistresourcetemplatesresult.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolListResourceTemplatesResultTest)

McpProtocolListResourceTemplatesResultTest::McpProtocolListResourceTemplatesResultTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolListResourceTemplatesResultTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolListResourceTemplatesResult w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.nextCursor().has_value());
    QVERIFY(w.resourceTemplates().isEmpty());
}
#include "moc_mcpprotocollistresourcetemplatesresulttest.cpp"
