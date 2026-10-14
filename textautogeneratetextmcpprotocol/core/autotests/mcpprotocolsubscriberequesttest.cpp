/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolsubscriberequesttest.h"
#include "impl/mcpprotocolsubscriberequest.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolSubscribeRequestTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolSubscribeRequestTest::McpProtocolSubscribeRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolSubscribeRequestTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscribeRequest w;
    QCOMPARE(w.type(), "resources/subscribe"_ba);
    // TODO
}

void McpProtocolSubscribeRequestTest::shouldRejectMissingRequiredFields()
{
    using namespace TextAutoGenerateTextMcpProtocolCore;
    const QJsonObject obj{{"jsonrpc"_L1, u"2.0"_s},
                          {"method"_L1, u"resources/subscribe"_s},
                          {"id"_L1, u"abc"_s},
                          {"params"_L1, QJsonObject{{"uri"_L1, u"file:///foo"_s}}}};
    const McpProtocolSubscribeRequest request = McpProtocolSubscribeRequest::fromJson(obj);
    QCOMPARE(request.params().uri(), u"file:///foo"_s);
    QCOMPARE(McpProtocolSubscribeRequest::toJson(request), obj);

    // Missing id
    QJsonObject withoutId = obj;
    withoutId.remove("id"_L1);
    QCOMPARE(McpProtocolSubscribeRequest::fromJson(withoutId), McpProtocolSubscribeRequest());
    // Missing params
    QJsonObject withoutParams = obj;
    withoutParams.remove("params"_L1);
    QCOMPARE(McpProtocolSubscribeRequest::fromJson(withoutParams), McpProtocolSubscribeRequest());
    // Params without uri
    QJsonObject withoutUri = obj;
    withoutUri["params"_L1] = QJsonObject();
    QCOMPARE(McpProtocolSubscribeRequest::fromJson(withoutUri), McpProtocolSubscribeRequest());
}

#include "moc_mcpprotocolsubscriberequesttest.cpp"
