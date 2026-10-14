/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolcanceltaskrequesttest.h"
#include "impl/mcpprotocolcanceltaskrequest.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolCancelTaskRequestTest)

McpProtocolCancelTaskRequestTest::McpProtocolCancelTaskRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolCancelTaskRequestTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolCancelTaskRequest w;
    // TODO
}
void McpProtocolCancelTaskRequestTest::shouldRejectMissingRequiredFields()
{
    using namespace Qt::Literals::StringLiterals;
    using namespace TextAutoGenerateTextMcpProtocolCore;
    QJsonObject params;
    params["taskId"_L1] = u"task-1"_s;
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["id"_L1] = 1;
    obj["method"_L1] = QString::fromLatin1(McpProtocolCancelTaskRequest::type());
    obj["params"_L1] = params;
    QVERIFY(!(McpProtocolCancelTaskRequest::fromJson(obj) == McpProtocolCancelTaskRequest()));

    QJsonObject missingId = obj;
    missingId.remove("id"_L1);
    QCOMPARE(McpProtocolCancelTaskRequest::fromJson(missingId), McpProtocolCancelTaskRequest());

    QJsonObject invalidId = obj;
    invalidId["id"_L1] = true;
    QCOMPARE(McpProtocolCancelTaskRequest::fromJson(invalidId), McpProtocolCancelTaskRequest());

    QJsonObject missingParams = obj;
    missingParams.remove("params"_L1);
    QCOMPARE(McpProtocolCancelTaskRequest::fromJson(missingParams), McpProtocolCancelTaskRequest());

    QJsonObject invalidParams = obj;
    invalidParams["params"_L1] = QJsonObject();
    QCOMPARE(McpProtocolCancelTaskRequest::fromJson(invalidParams), McpProtocolCancelTaskRequest());
}

#include "moc_mcpprotocolcanceltaskrequesttest.cpp"
