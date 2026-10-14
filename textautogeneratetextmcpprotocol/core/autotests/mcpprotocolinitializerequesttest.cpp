/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolinitializerequesttest.h"
#include "impl/mcpprotocolinitializerequest.h"
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolInitializeRequestTest)

McpProtocolInitializeRequestTest::McpProtocolInitializeRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolInitializeRequestTest::shouldAlwaysSerializeParams()
{
    // "params" is required by specification
    const QJsonObject obj = TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeRequest::toJson({});
    QCOMPARE(obj.value("method"_L1).toString(), u"initialize"_s);
    const QJsonObject params = obj.value("params"_L1).toObject();
    QVERIFY(params.contains("protocolVersion"_L1));
    QVERIFY(params.contains("capabilities"_L1));
    QVERIFY(params.contains("clientInfo"_L1));
}

void McpProtocolInitializeRequestTest::shouldLoadAndSaveRequest()
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeRequestParams params;
    params.setProtocolVersion(u"2025-11-25"_s);
    auto clientInfo = params.clientInfo();
    clientInfo.setName(u"client"_s);
    clientInfo.setVersion(u"1.0"_s);
    params.setClientInfo(clientInfo);
    TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeRequest request;
    request.setId(qint64(3));
    request.setParams(params);
    const QJsonObject obj = TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeRequest::toJson(request);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeRequest::fromJson(obj), request);
}

void McpProtocolInitializeRequestTest::shouldRejectMissingRequiredFields()
{
    using namespace TextAutoGenerateTextMcpProtocolCore;
    QJsonObject clientInfo;
    clientInfo["name"_L1] = u"client"_s;
    clientInfo["version"_L1] = u"1.0"_s;
    QJsonObject params;
    params["protocolVersion"_L1] = u"2025-11-25"_s;
    params["capabilities"_L1] = QJsonObject();
    params["clientInfo"_L1] = clientInfo;
    QJsonObject valid;
    valid["jsonrpc"_L1] = u"2.0"_s;
    valid["id"_L1] = 1;
    valid["method"_L1] = u"initialize"_s;
    valid["params"_L1] = params;
    QVERIFY(McpProtocolInitializeRequest::fromJson(valid) != McpProtocolInitializeRequest());

    for (const QString &key : {u"id"_s, u"params"_s}) {
        QJsonObject obj = valid;
        obj.remove(key);
        QCOMPARE(McpProtocolInitializeRequest::fromJson(obj), McpProtocolInitializeRequest());
    }
    {
        QJsonObject obj = valid;
        params.remove(u"clientInfo"_s);
        obj["params"_L1] = params;
        QCOMPARE(McpProtocolInitializeRequest::fromJson(obj), McpProtocolInitializeRequest());
    }
}

#include "moc_mcpprotocolinitializerequesttest.cpp"
