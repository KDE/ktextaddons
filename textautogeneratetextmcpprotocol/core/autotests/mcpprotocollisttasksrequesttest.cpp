/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocollisttasksrequesttest.h"
#include "impl/mcpprotocollisttasksrequest.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolListTasksRequestTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolListTasksRequestTest::McpProtocolListTasksRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolListTasksRequestTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolListTasksRequest w;
    QCOMPARE(w.type(), "tasks/list"_ba);
    QVERIFY(!w.params().has_value());
}

void McpProtocolListTasksRequestTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolListTasksRequest;
    QJsonObject valid;
    valid["jsonrpc"_L1] = u"2.0"_s;
    valid["id"_L1] = 1;
    valid["method"_L1] = u"tasks/list"_s;
    QVERIFY(McpProtocolListTasksRequest::fromJson(valid) != McpProtocolListTasksRequest());

    QJsonObject obj = valid;
    obj.remove(u"id"_s);
    QCOMPARE(McpProtocolListTasksRequest::fromJson(obj), McpProtocolListTasksRequest());

    obj = valid;
    obj["id"_L1] = true;
    QCOMPARE(McpProtocolListTasksRequest::fromJson(obj), McpProtocolListTasksRequest());
}

#include "moc_mcpprotocollisttasksrequesttest.cpp"
