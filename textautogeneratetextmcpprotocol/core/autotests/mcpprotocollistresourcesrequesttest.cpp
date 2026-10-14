/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocollistresourcesrequesttest.h"
#include "impl/mcpprotocollistresourcesrequest.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolListResourcesRequestTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolListResourcesRequestTest::McpProtocolListResourcesRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolListResourcesRequestTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolListResourcesRequest w;
    QCOMPARE(w.type(), "resources/list"_ba);
    // TODO
}

void McpProtocolListResourcesRequestTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolListResourcesRequest;
    QJsonObject valid;
    valid["jsonrpc"_L1] = u"2.0"_s;
    valid["id"_L1] = 1;
    valid["method"_L1] = u"resources/list"_s;
    QVERIFY(McpProtocolListResourcesRequest::fromJson(valid) != McpProtocolListResourcesRequest());

    QJsonObject obj = valid;
    obj.remove(u"id"_s);
    QCOMPARE(McpProtocolListResourcesRequest::fromJson(obj), McpProtocolListResourcesRequest());

    obj = valid;
    obj["id"_L1] = true;
    QCOMPARE(McpProtocolListResourcesRequest::fromJson(obj), McpProtocolListResourcesRequest());
}

#include "moc_mcpprotocollistresourcesrequesttest.cpp"
