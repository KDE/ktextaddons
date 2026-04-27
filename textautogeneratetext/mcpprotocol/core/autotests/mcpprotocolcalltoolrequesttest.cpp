/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolcalltoolrequesttest.h"
#include "mcpprotocolcalltoolrequest.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolCallToolRequestTest)

McpProtocolCallToolRequestTest::McpProtocolCallToolRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolCallToolRequestTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolCallToolRequest w;
    // TODO
}
#include "moc_mcpprotocolcalltoolrequesttest.cpp"
