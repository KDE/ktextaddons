/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoljsonrpcerrorresponsetest.h"
#include "mcpprotocoljsonrpcerrorresponse.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolJSONRPCErrorResponseTest)

McpProtocolJSONRPCErrorResponseTest::McpProtocolJSONRPCErrorResponseTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolJSONRPCErrorResponseTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolJSONRPCErrorResponse w;
    QVERIFY(!w.id().has_value());
    // TODO QVERIFY(w.uri().isEmpty());
}
#include "moc_mcpprotocoljsonrpcerrorresponsetest.cpp"
