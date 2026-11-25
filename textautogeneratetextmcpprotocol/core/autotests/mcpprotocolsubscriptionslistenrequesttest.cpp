/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolsubscriptionslistenrequesttest.h"
#include "impl/mcpprotocolsubscriptionslistenrequest.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolSubscriptionsListenRequestTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSubscriptionsListenRequestTest::McpProtocolSubscriptionsListenRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolSubscriptionsListenRequestTest::shouldHaveDefaultValues()
{
    const McpProtocolSubscriptionsListenRequest w;
    QCOMPARE(w.type(), "subscriptions/listen"_ba);
    QVERIFY(!w.params().isValid());
}

void McpProtocolSubscriptionsListenRequestTest::shouldConvertJson()
{
    const QJsonObject obj{
        {"jsonrpc"_L1, u"2.0"_s},
        {"method"_L1, u"subscriptions/listen"_s},
        {"id"_L1, 3},
        {"params"_L1,
         QJsonObject{{"notifications"_L1, QJsonObject{{"resourcesListChanged"_L1, true}, {"resourceSubscriptions"_L1, QJsonArray{u"file:///a.txt"_s}}}}}}};
    const McpProtocolSubscriptionsListenRequest request = McpProtocolSubscriptionsListenRequest::fromJson(obj);
    QCOMPARE(request.id(), McpProtocolUtils::RequestId(qint64(3)));
    QVERIFY(request.params().isValid());
    QCOMPARE(request.params().notifications()->resourcesListChanged(), true);
    QCOMPARE(McpProtocolSubscriptionsListenRequest::toJson(request), obj);
}

void McpProtocolSubscriptionsListenRequestTest::shouldRejectMissingRequiredFields()
{
    QJsonObject obj{{"jsonrpc"_L1, u"2.0"_s},
                    {"method"_L1, u"subscriptions/listen"_s},
                    {"id"_L1, u"abc"_s},
                    {"params"_L1, QJsonObject{{"notifications"_L1, QJsonObject()}}}};
    QCOMPARE(McpProtocolSubscriptionsListenRequest::toJson(McpProtocolSubscriptionsListenRequest::fromJson(obj)), obj);

    obj["params"_L1] = QJsonObject();
    QCOMPARE(McpProtocolSubscriptionsListenRequest::fromJson(obj), McpProtocolSubscriptionsListenRequest());
    obj.remove("params"_L1);
    QCOMPARE(McpProtocolSubscriptionsListenRequest::fromJson(obj), McpProtocolSubscriptionsListenRequest());
    obj["params"_L1] = QJsonObject{{"notifications"_L1, QJsonObject()}};

    obj.remove("id"_L1);
    QCOMPARE(McpProtocolSubscriptionsListenRequest::fromJson(obj), McpProtocolSubscriptionsListenRequest());
    obj["id"_L1] = u"abc"_s;

    obj["method"_L1] = u"server/discover"_s;
    QCOMPARE(McpProtocolSubscriptionsListenRequest::fromJson(obj), McpProtocolSubscriptionsListenRequest());
    obj["method"_L1] = u"subscriptions/listen"_s;

    obj["jsonrpc"_L1] = u"1.0"_s;
    QCOMPARE(McpProtocolSubscriptionsListenRequest::fromJson(obj), McpProtocolSubscriptionsListenRequest());
}

#include "moc_mcpprotocolsubscriptionslistenrequesttest.cpp"
