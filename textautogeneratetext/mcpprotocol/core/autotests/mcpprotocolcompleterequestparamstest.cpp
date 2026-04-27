/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolcompleterequestparamstest.h"
#include "mcpprotocolcompleterequestparams.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolCompleteRequestParamsTest)

McpProtocolCompleteRequestParamsTest::McpProtocolCompleteRequestParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolCompleteRequestParamsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolCompleteRequestParams w;
    QVERIFY(!w.meta().has_value());
    // TODO
}
#include "moc_mcpprotocolcompleterequestparamstest.cpp"
