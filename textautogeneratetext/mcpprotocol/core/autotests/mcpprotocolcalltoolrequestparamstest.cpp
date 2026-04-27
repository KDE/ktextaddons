/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolcalltoolrequestparamstest.h"
#include "mcpprotocolcalltoolrequestparams.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolCallToolRequestParamsTest)

McpProtocolCallToolRequestParamsTest::McpProtocolCallToolRequestParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolCallToolRequestParamsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolCallToolRequestParams w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.arguments().has_value());
    QVERIFY(!w.task().has_value());
    QVERIFY(w.name().isEmpty());
}
#include "moc_mcpprotocolcalltoolrequestparamstest.cpp"
