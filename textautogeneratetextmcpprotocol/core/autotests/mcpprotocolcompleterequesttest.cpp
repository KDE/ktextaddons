/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolcompleterequesttest.h"
#include "impl/mcpprotocolcompleterequest.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolCompleteRequestTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolCompleteRequestTest::McpProtocolCompleteRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolCompleteRequestTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolCompleteRequest w;
    QCOMPARE(w.type(), "completion/complete"_ba);
    // TODO
}
void McpProtocolCompleteRequestTest::shouldRejectMissingRequiredFields()
{
    using namespace Qt::Literals::StringLiterals;
    using namespace TextAutoGenerateTextMcpProtocolCore;
    QJsonObject params;
    QJsonObject ref;
    ref["type"_L1] = u"ref/prompt"_s;
    ref["name"_L1] = u"prompt"_s;
    QJsonObject argument;
    argument["name"_L1] = u"arg"_s;
    argument["value"_L1] = u"val"_s;
    params["ref"_L1] = ref;
    params["argument"_L1] = argument;
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["id"_L1] = 1;
    obj["method"_L1] = QString::fromLatin1(McpProtocolCompleteRequest::type());
    obj["params"_L1] = params;
    QVERIFY(!(McpProtocolCompleteRequest::fromJson(obj) == McpProtocolCompleteRequest()));

    QJsonObject missingId = obj;
    missingId.remove("id"_L1);
    QCOMPARE(McpProtocolCompleteRequest::fromJson(missingId), McpProtocolCompleteRequest());

    QJsonObject invalidId = obj;
    invalidId["id"_L1] = true;
    QCOMPARE(McpProtocolCompleteRequest::fromJson(invalidId), McpProtocolCompleteRequest());

    QJsonObject missingParams = obj;
    missingParams.remove("params"_L1);
    QCOMPARE(McpProtocolCompleteRequest::fromJson(missingParams), McpProtocolCompleteRequest());

    QJsonObject invalidParams = obj;
    invalidParams["params"_L1] = QJsonObject();
    QCOMPARE(McpProtocolCompleteRequest::fromJson(invalidParams), McpProtocolCompleteRequest());
}

#include "moc_mcpprotocolcompleterequesttest.cpp"
