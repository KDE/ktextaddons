/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolpromptmessagetest.h"
#include "impl/mcpprotocolpromptmessage.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolPromptMessageTest)

McpProtocolPromptMessageTest::McpProtocolPromptMessageTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolPromptMessageTest::shouldhaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolPromptMessage w;
    QCOMPARE(w.role(), TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::Role::Unknown);
}

#include "moc_mcpprotocolpromptmessagetest.cpp"
