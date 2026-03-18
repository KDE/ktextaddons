/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolpromptargumenttest.h"
#include "mcpprotocolpromptargument.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolPromptArgumentTest)

McpProtocolPromptArgumentTest::McpProtocolPromptArgumentTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolPromptArgumentTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolPromptArgument w;
    QVERIFY(!w.description().has_value());
    QVERIFY(!w.required().has_value());
    QVERIFY(!w.title().has_value());
    QVERIFY(w.name().isEmpty());
}
#include "moc_mcpprotocolpromptargumenttest.cpp"
