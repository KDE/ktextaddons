/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolgettaskrequesttest.h"
#include "impl/mcpprotocolgettaskrequest.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolGetTaskRequestTest)

McpProtocolGetTaskRequestTest::McpProtocolGetTaskRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolGetTaskRequestTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolGetTaskRequest w;
    // TODO
}

void McpProtocolGetTaskRequestTest::shouldRejectMissingRequiredFields()
{
    using namespace TextAutoGenerateTextMcpProtocolCore;
    using namespace Qt::Literals::StringLiterals;
    QJsonObject params;
    params["taskId"_L1] = u"task-1"_s;
    QJsonObject valid;
    valid["jsonrpc"_L1] = u"2.0"_s;
    valid["id"_L1] = 1;
    valid["method"_L1] = u"tasks/get"_s;
    valid["params"_L1] = params;
    const McpProtocolGetTaskRequest request = McpProtocolGetTaskRequest::fromJson(valid);
    QVERIFY(request != McpProtocolGetTaskRequest());
    QCOMPARE(request.params().taskId(), u"task-1"_s);

    for (const QString &key : {u"id"_s, u"params"_s}) {
        QJsonObject obj = valid;
        obj.remove(key);
        QCOMPARE(McpProtocolGetTaskRequest::fromJson(obj), McpProtocolGetTaskRequest());
    }
    {
        QJsonObject obj = valid;
        obj["params"_L1] = QJsonObject();
        QCOMPARE(McpProtocolGetTaskRequest::fromJson(obj), McpProtocolGetTaskRequest());
    }
    {
        QJsonObject obj = valid;
        obj["id"_L1] = QJsonObject();
        QCOMPARE(McpProtocolGetTaskRequest::fromJson(obj), McpProtocolGetTaskRequest());
    }
}

#include "moc_mcpprotocolgettaskrequesttest.cpp"
