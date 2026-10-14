/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocollistresourcetemplatesrequesttest.h"
#include "impl/mcpprotocollistresourcetemplatesrequest.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolListResourceTemplatesRequestTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolListResourceTemplatesRequestTest::McpProtocolListResourceTemplatesRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolListResourceTemplatesRequestTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolListResourceTemplatesRequest w;
    QCOMPARE(w.type(), "resources/templates/list"_ba);
    QVERIFY(!w.params().has_value());
    // TODO
}

void McpProtocolListResourceTemplatesRequestTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolListResourceTemplatesRequest;
    QJsonObject valid;
    valid["jsonrpc"_L1] = u"2.0"_s;
    valid["id"_L1] = 1;
    valid["method"_L1] = u"resources/templates/list"_s;
    QVERIFY(McpProtocolListResourceTemplatesRequest::fromJson(valid) != McpProtocolListResourceTemplatesRequest());

    QJsonObject obj = valid;
    obj.remove(u"id"_s);
    QCOMPARE(McpProtocolListResourceTemplatesRequest::fromJson(obj), McpProtocolListResourceTemplatesRequest());

    obj = valid;
    obj["id"_L1] = true;
    QCOMPARE(McpProtocolListResourceTemplatesRequest::fromJson(obj), McpProtocolListResourceTemplatesRequest());
}

#include "moc_mcpprotocollistresourcetemplatesrequesttest.cpp"
