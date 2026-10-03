/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolcalltoolrequesttest.h"
#include "impl/mcpprotocolcalltoolrequest.h"
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolCallToolRequestTest)

McpProtocolCallToolRequestTest::McpProtocolCallToolRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolCallToolRequestTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolCallToolRequest w;
    QCOMPARE(w.type(), "tools/call"_ba);
    QVERIFY(w.params().name().isEmpty());
}
#include "moc_mcpprotocolcalltoolrequesttest.cpp"
