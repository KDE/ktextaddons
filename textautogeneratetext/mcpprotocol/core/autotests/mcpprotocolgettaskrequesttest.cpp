/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolgettaskrequesttest.h"
#include "mcpprotocolgettaskrequest.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolGetTaskRequestTest)

McpProtocolGetTaskRequestTest::McpProtocolGetTaskRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolGetTaskRequestTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolGetTaskRequest w;
    // TODO
}
#include "moc_mcpprotocolgettaskrequesttest.cpp"
