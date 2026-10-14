/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocollisttoolsrequesttest.h"
#include "impl/mcpprotocollisttoolsrequest.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolListToolsRequestTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolListToolsRequestTest::McpProtocolListToolsRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolListToolsRequestTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolListToolsRequest w;
    QCOMPARE(w.type(), "tools/list"_ba);
    // TODO
}

void McpProtocolListToolsRequestTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolListToolsRequest;
    QJsonObject valid;
    valid["jsonrpc"_L1] = u"2.0"_s;
    valid["id"_L1] = 1;
    valid["method"_L1] = u"tools/list"_s;
    QVERIFY(McpProtocolListToolsRequest::fromJson(valid) != McpProtocolListToolsRequest());

    QJsonObject obj = valid;
    obj.remove(u"id"_s);
    QCOMPARE(McpProtocolListToolsRequest::fromJson(obj), McpProtocolListToolsRequest());

    obj = valid;
    obj["id"_L1] = true;
    QCOMPARE(McpProtocolListToolsRequest::fromJson(obj), McpProtocolListToolsRequest());
}

#include "moc_mcpprotocollisttoolsrequesttest.cpp"
