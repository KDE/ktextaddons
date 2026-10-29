/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoldiscoverrequesttest.h"
#include "impl/mcpprotocoldiscoverrequest.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolDiscoverRequestTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolDiscoverRequestTest::McpProtocolDiscoverRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolDiscoverRequestTest::shouldHaveDefaultValues()
{
    const McpProtocolDiscoverRequest w;
    QCOMPARE(w.type(), "server/discover"_ba);
    QVERIFY(!w.params().meta().has_value());
}

void McpProtocolDiscoverRequestTest::shouldConvertJson()
{
    const QJsonObject obj{{"jsonrpc"_L1, u"2.0"_s}, {"method"_L1, u"server/discover"_s}, {"id"_L1, 1}, {"params"_L1, QJsonObject()}};
    const McpProtocolDiscoverRequest request = McpProtocolDiscoverRequest::fromJson(obj);
    QCOMPARE(request.id(), McpProtocolUtils::RequestId(qint64(1)));
    QCOMPARE(McpProtocolDiscoverRequest::toJson(request), obj);
}

void McpProtocolDiscoverRequestTest::shouldRejectMissingRequiredFields()
{
    QJsonObject obj{{"jsonrpc"_L1, u"2.0"_s}, {"method"_L1, u"server/discover"_s}, {"id"_L1, u"abc"_s}, {"params"_L1, QJsonObject()}};
    QCOMPARE(McpProtocolDiscoverRequest::toJson(McpProtocolDiscoverRequest::fromJson(obj)), obj);

    obj.remove("params"_L1);
    QCOMPARE(McpProtocolDiscoverRequest::fromJson(obj), McpProtocolDiscoverRequest());
    obj["params"_L1] = QJsonObject();

    obj.remove("id"_L1);
    QCOMPARE(McpProtocolDiscoverRequest::fromJson(obj), McpProtocolDiscoverRequest());
    obj["id"_L1] = QJsonObject();
    QCOMPARE(McpProtocolDiscoverRequest::fromJson(obj), McpProtocolDiscoverRequest());
    obj["id"_L1] = u"abc"_s;

    obj["method"_L1] = u"initialize"_s;
    QCOMPARE(McpProtocolDiscoverRequest::fromJson(obj), McpProtocolDiscoverRequest());
}

#include "moc_mcpprotocoldiscoverrequesttest.cpp"
