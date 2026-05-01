/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolgettaskpayloadrequesttest.h"
#include "impl/mcpprotocolgettaskpayloadrequest.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolGetTaskPayloadRequestTest)

McpProtocolGetTaskPayloadRequestTest::McpProtocolGetTaskPayloadRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolGetTaskPayloadRequestTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolGetTaskPayloadRequest w;
    // TODO
}
#include "moc_mcpprotocolgettaskpayloadrequesttest.cpp"
