/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolcanceltaskrequesttest.h"
#include "mcpprotocolcanceltaskrequest.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolCancelTaskRequestTest)

McpProtocolCancelTaskRequestTest::McpProtocolCancelTaskRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolCancelTaskRequestTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolCancelTaskRequest w;
    // TODO
}
#include "moc_mcpprotocolcanceltaskrequesttest.cpp"
