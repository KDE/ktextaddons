/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolgettaskpayloadrequesttest.h"
#include "impl/mcpprotocolgettaskpayloadrequest.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolGetTaskPayloadRequestTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;

McpProtocolGetTaskPayloadRequestTest::McpProtocolGetTaskPayloadRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolGetTaskPayloadRequestTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolGetTaskPayloadRequest w;
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolGetTaskPayloadRequest::type(), "tasks/result"_ba);
    QVERIFY(w.params().taskId().isEmpty());
}
void McpProtocolGetTaskPayloadRequestTest::shouldConvertJson()
{
    QJsonObject params;
    params["taskId"_L1] = u"task-42"_s;
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["id"_L1] = 7;
    obj["method"_L1] = u"tasks/result"_s;
    obj["params"_L1] = params;

    const McpProtocolGetTaskPayloadRequest request = McpProtocolGetTaskPayloadRequest::fromJson(obj);
    QCOMPARE(request.params().taskId(), u"task-42"_s);
    QCOMPARE(McpProtocolGetTaskPayloadRequest::Params::fromJson(params).taskId(), u"task-42"_s);
    QCOMPARE(McpProtocolGetTaskPayloadRequest::toJson(request), obj);

    QJsonObject wrongMethod = obj;
    wrongMethod["method"_L1] = u"tasks/get"_s;
    QCOMPARE(McpProtocolGetTaskPayloadRequest::fromJson(wrongMethod), McpProtocolGetTaskPayloadRequest());

    QJsonObject wrongJsonRpc = obj;
    wrongJsonRpc["jsonrpc"_L1] = u"1.0"_s;
    QCOMPARE(McpProtocolGetTaskPayloadRequest::fromJson(wrongJsonRpc), McpProtocolGetTaskPayloadRequest());
}

void McpProtocolGetTaskPayloadRequestTest::shouldRejectMissingRequiredFields()
{
    using namespace Qt::Literals::StringLiterals;
    using namespace TextAutoGenerateTextMcpProtocolCore;
    QJsonObject params;
    params["taskId"_L1] = u"task-1"_s;
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["id"_L1] = 1;
    obj["method"_L1] = QString::fromLatin1(McpProtocolGetTaskPayloadRequest::type());
    obj["params"_L1] = params;
    QVERIFY(!(McpProtocolGetTaskPayloadRequest::fromJson(obj) == McpProtocolGetTaskPayloadRequest()));

    QJsonObject missingId = obj;
    missingId.remove("id"_L1);
    QCOMPARE(McpProtocolGetTaskPayloadRequest::fromJson(missingId), McpProtocolGetTaskPayloadRequest());

    QJsonObject invalidId = obj;
    invalidId["id"_L1] = true;
    QCOMPARE(McpProtocolGetTaskPayloadRequest::fromJson(invalidId), McpProtocolGetTaskPayloadRequest());

    QJsonObject missingParams = obj;
    missingParams.remove("params"_L1);
    QCOMPARE(McpProtocolGetTaskPayloadRequest::fromJson(missingParams), McpProtocolGetTaskPayloadRequest());

    QJsonObject invalidParams = obj;
    invalidParams["params"_L1] = QJsonObject();
    QCOMPARE(McpProtocolGetTaskPayloadRequest::fromJson(invalidParams), McpProtocolGetTaskPayloadRequest());
}

#include "moc_mcpprotocolgettaskpayloadrequesttest.cpp"
