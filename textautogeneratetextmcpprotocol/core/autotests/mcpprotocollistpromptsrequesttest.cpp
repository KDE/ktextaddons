/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocollistpromptsrequesttest.h"
#include "impl/mcpprotocollistpromptsrequest.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolListPromptsRequestTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolListPromptsRequestTest::McpProtocolListPromptsRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolListPromptsRequestTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolListPromptsRequest w;
    QCOMPARE(w.type(), "prompts/list"_ba);
    QVERIFY(!w.params().has_value());
    // TODO
}

void McpProtocolListPromptsRequestTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolListPromptsRequest;
    QJsonObject valid;
    valid["jsonrpc"_L1] = u"2.0"_s;
    valid["id"_L1] = 1;
    valid["method"_L1] = u"prompts/list"_s;
    QVERIFY(McpProtocolListPromptsRequest::fromJson(valid) != McpProtocolListPromptsRequest());

    QJsonObject obj = valid;
    obj.remove(u"id"_s);
    QCOMPARE(McpProtocolListPromptsRequest::fromJson(obj), McpProtocolListPromptsRequest());

    obj = valid;
    obj["id"_L1] = true;
    QCOMPARE(McpProtocolListPromptsRequest::fromJson(obj), McpProtocolListPromptsRequest());
}

#include "moc_mcpprotocollistpromptsrequesttest.cpp"
