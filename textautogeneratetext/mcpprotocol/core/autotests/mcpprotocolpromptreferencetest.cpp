/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolpromptreferencetest.h"
#include "impl/mcpprotocolpromptreference.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolPromptReferenceTest)

McpProtocolPromptReferenceTest::McpProtocolPromptReferenceTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolPromptReferenceTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolPromptReference w;
    QVERIFY(!w.title().has_value());
    QVERIFY(w.name().isEmpty());
}
#include "moc_mcpprotocolpromptreferencetest.cpp"
