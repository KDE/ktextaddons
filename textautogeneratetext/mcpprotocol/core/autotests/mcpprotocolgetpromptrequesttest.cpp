/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolgetpromptrequesttest.h"
#include "mcpprotocolgetpromptrequest.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolGetPromptRequestTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolGetPromptRequestTest::McpProtocolGetPromptRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolGetPromptRequestTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolGetPromptRequest w;
    QCOMPARE(w.type(), "prompts/get"_ba);
    // TODO
}
#include "moc_mcpprotocolgetpromptrequesttest.cpp"
