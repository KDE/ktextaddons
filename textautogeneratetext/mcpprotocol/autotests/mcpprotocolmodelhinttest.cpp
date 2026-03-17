/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolmodelhinttest.h"
#include "mcpprotocolmodelhint.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolModelHintTest)

McpProtocolModelHintTest::McpProtocolModelHintTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolModelHintTest::shouldhaveDefaultValues()
{
    const McpProtocol::McpProtocolModelHint w;
    QVERIFY(!w.name().has_value());
}

#include "moc_mcpprotocolmodelhinttest.cpp"
