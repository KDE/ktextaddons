/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolelicitrequesttest.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitRequest>

QTEST_GUILESS_MAIN(McpProtocolElicitRequestTest)

McpProtocolElicitRequestTest::McpProtocolElicitRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolElicitRequestTest::shouldHaveDefaultValues()
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequest request;
    QCOMPARE(request.type(), "elicitation/create");
}

void McpProtocolElicitRequestTest::shouldRejectMissingRequiredFields()
{
    using namespace Qt::Literals::StringLiterals;
    using namespace TextAutoGenerateTextMcpProtocolCore;
    QJsonObject params;
    QJsonObject requestedSchema;
    requestedSchema["type"_L1] = u"object"_s;
    requestedSchema["properties"_L1] = QJsonObject();
    params["message"_L1] = u"Your name?"_s;
    params["requestedSchema"_L1] = requestedSchema;
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["id"_L1] = 1;
    obj["method"_L1] = QString::fromLatin1(McpProtocolElicitRequest::type());
    obj["params"_L1] = params;
    QVERIFY(!(McpProtocolElicitRequest::fromJson(obj) == McpProtocolElicitRequest()));

    QJsonObject missingId = obj;
    missingId.remove("id"_L1);
    QCOMPARE(McpProtocolElicitRequest::fromJson(missingId), McpProtocolElicitRequest());

    QJsonObject invalidId = obj;
    invalidId["id"_L1] = true;
    QCOMPARE(McpProtocolElicitRequest::fromJson(invalidId), McpProtocolElicitRequest());

    QJsonObject missingParams = obj;
    missingParams.remove("params"_L1);
    QCOMPARE(McpProtocolElicitRequest::fromJson(missingParams), McpProtocolElicitRequest());

    QJsonObject invalidParams = obj;
    invalidParams["params"_L1] = QJsonObject();
    QCOMPARE(McpProtocolElicitRequest::fromJson(invalidParams), McpProtocolElicitRequest());
}

#include "moc_mcpprotocolelicitrequesttest.cpp"
