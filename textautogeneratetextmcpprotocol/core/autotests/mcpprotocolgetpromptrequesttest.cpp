/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolgetpromptrequesttest.h"
#include "impl/mcpprotocolgetpromptrequest.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolGetPromptRequestTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolGetPromptRequestTest::McpProtocolGetPromptRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolGetPromptRequestTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolGetPromptRequest w;
    QCOMPARE(w.type(), "prompts/get"_ba);
    // TODO
}
void McpProtocolGetPromptRequestTest::shouldRejectMissingRequiredFields()
{
    using namespace Qt::Literals::StringLiterals;
    using namespace TextAutoGenerateTextMcpProtocolCore;
    QJsonObject params;
    params["name"_L1] = u"prompt"_s;
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["id"_L1] = 1;
    obj["method"_L1] = QString::fromLatin1(McpProtocolGetPromptRequest::type());
    obj["params"_L1] = params;
    QVERIFY(!(McpProtocolGetPromptRequest::fromJson(obj) == McpProtocolGetPromptRequest()));

    QJsonObject missingId = obj;
    missingId.remove("id"_L1);
    QCOMPARE(McpProtocolGetPromptRequest::fromJson(missingId), McpProtocolGetPromptRequest());

    QJsonObject invalidId = obj;
    invalidId["id"_L1] = true;
    QCOMPARE(McpProtocolGetPromptRequest::fromJson(invalidId), McpProtocolGetPromptRequest());

    QJsonObject missingParams = obj;
    missingParams.remove("params"_L1);
    QCOMPARE(McpProtocolGetPromptRequest::fromJson(missingParams), McpProtocolGetPromptRequest());

    QJsonObject invalidParams = obj;
    invalidParams["params"_L1] = QJsonObject();
    QCOMPARE(McpProtocolGetPromptRequest::fromJson(invalidParams), McpProtocolGetPromptRequest());
}

#include "moc_mcpprotocolgetpromptrequesttest.cpp"
