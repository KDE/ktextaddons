/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolpingrequesttest.h"
#include "impl/mcpprotocolpingrequest.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolPingRequestTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolPingRequestTest::McpProtocolPingRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolPingRequestTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolPingRequest w;
    QCOMPARE(w.type(), "ping"_ba);
    QVERIFY(!w.params().has_value());
    // TODO
}

void McpProtocolPingRequestTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolPingRequest;
    QJsonObject obj{{"jsonrpc"_L1, u"2.0"_s}, {"method"_L1, u"ping"_s}, {"id"_L1, u"abc"_s}};
    QCOMPARE(McpProtocolPingRequest::toJson(McpProtocolPingRequest::fromJson(obj)), obj);
    obj.remove("id"_L1);
    QCOMPARE(McpProtocolPingRequest::fromJson(obj), McpProtocolPingRequest());
    obj["id"_L1] = QJsonObject();
    QCOMPARE(McpProtocolPingRequest::fromJson(obj), McpProtocolPingRequest());
}

#include "moc_mcpprotocolpingrequesttest.cpp"
