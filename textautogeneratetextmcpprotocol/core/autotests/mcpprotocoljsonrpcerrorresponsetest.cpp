/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoljsonrpcerrorresponsetest.h"
#include "impl/mcpprotocoljsonrpcerrorresponse.h"
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolJSONRPCErrorResponseTest)

McpProtocolJSONRPCErrorResponseTest::McpProtocolJSONRPCErrorResponseTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolJSONRPCErrorResponseTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolJSONRPCErrorResponse w;
    QVERIFY(!w.id().has_value());
    QCOMPARE(w.error().code(), 0);
}

void McpProtocolJSONRPCErrorResponseTest::shouldLoadNullId()
{
    // Parse error: server can't know request id
    const QJsonObject obj{{"jsonrpc"_L1, u"2.0"_s},
                          {"id"_L1, QJsonValue::Null},
                          {"error"_L1, QJsonObject{{"code"_L1, -32700}, {"message"_L1, u"Parse error"_s}}}};
    const auto response = TextAutoGenerateTextMcpProtocolCore::McpProtocolJSONRPCErrorResponse::fromJson(obj);
    QVERIFY(!response.id().has_value());
    QCOMPARE(response.error().code(), -32700);
    QVERIFY(!TextAutoGenerateTextMcpProtocolCore::McpProtocolJSONRPCErrorResponse::toJson(response).value("id"_L1).isString());
}

void McpProtocolJSONRPCErrorResponseTest::shouldLoadAndSaveResponse()
{
    const QJsonObject obj{{"jsonrpc"_L1, u"2.0"_s}, {"id"_L1, 5}, {"error"_L1, QJsonObject{{"code"_L1, -32601}, {"message"_L1, u"Method not found"_s}}}};
    const auto response = TextAutoGenerateTextMcpProtocolCore::McpProtocolJSONRPCErrorResponse::fromJson(obj);
    QVERIFY(response.id().has_value());
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolJSONRPCErrorResponse::toJson(response), obj);
}
#include "moc_mcpprotocoljsonrpcerrorresponsetest.cpp"
