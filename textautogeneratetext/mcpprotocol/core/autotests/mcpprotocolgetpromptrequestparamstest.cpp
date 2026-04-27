/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolgetpromptrequestparamstest.h"
#include "mcpprotocolgetpromptrequestparams.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolGetPromptRequestParamsTest)

McpProtocolGetPromptRequestParamsTest::McpProtocolGetPromptRequestParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolGetPromptRequestParamsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolGetPromptRequestParams w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.arguments().has_value());
    QVERIFY(w.name().isEmpty());
}
#include "moc_mcpprotocolgetpromptrequestparamstest.cpp"
