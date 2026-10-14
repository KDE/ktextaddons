/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolunsubscriberequesttest.h"
#include "impl/mcpprotocolunsubscriberequest.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolUnsubscribeRequestTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolUnsubscribeRequestTest::McpProtocolUnsubscribeRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolUnsubscribeRequestTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolUnsubscribeRequest w;
    QCOMPARE(w.type(), "resources/unsubscribe"_ba);
    // TODO
}

void McpProtocolUnsubscribeRequestTest::shouldRejectMissingRequiredFields()
{
    using namespace TextAutoGenerateTextMcpProtocolCore;
    const QJsonObject obj{{"jsonrpc"_L1, u"2.0"_s},
                          {"method"_L1, u"resources/unsubscribe"_s},
                          {"id"_L1, u"abc"_s},
                          {"params"_L1, QJsonObject{{"uri"_L1, u"file:///foo"_s}}}};
    const McpProtocolUnsubscribeRequest request = McpProtocolUnsubscribeRequest::fromJson(obj);
    QCOMPARE(request.params().uri(), u"file:///foo"_s);
    QCOMPARE(McpProtocolUnsubscribeRequest::toJson(request), obj);

    // Missing id
    QJsonObject withoutId = obj;
    withoutId.remove("id"_L1);
    QCOMPARE(McpProtocolUnsubscribeRequest::fromJson(withoutId), McpProtocolUnsubscribeRequest());
    // Missing params
    QJsonObject withoutParams = obj;
    withoutParams.remove("params"_L1);
    QCOMPARE(McpProtocolUnsubscribeRequest::fromJson(withoutParams), McpProtocolUnsubscribeRequest());
    // Params without uri
    QJsonObject withoutUri = obj;
    withoutUri["params"_L1] = QJsonObject();
    QCOMPARE(McpProtocolUnsubscribeRequest::fromJson(withoutUri), McpProtocolUnsubscribeRequest());
}

#include "moc_mcpprotocolunsubscriberequesttest.cpp"
