/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolcalltoolrequesttest.h"
#include "impl/mcpprotocolcalltoolrequest.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolCallToolRequestTest)

McpProtocolCallToolRequestTest::McpProtocolCallToolRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolCallToolRequestTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolCallToolRequest w;
    QCOMPARE(w.type(), "tools/call"_ba);
    QVERIFY(w.params().name().isEmpty());
}
void McpProtocolCallToolRequestTest::shouldRejectMissingRequiredFields()
{
    using namespace Qt::Literals::StringLiterals;
    using namespace TextAutoGenerateTextMcpProtocolCore;
    QJsonObject params;
    params["name"_L1] = u"tool"_s;
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["id"_L1] = 1;
    obj["method"_L1] = QString::fromLatin1(McpProtocolCallToolRequest::type());
    obj["params"_L1] = params;
    QVERIFY(!(McpProtocolCallToolRequest::fromJson(obj) == McpProtocolCallToolRequest()));

    QJsonObject missingId = obj;
    missingId.remove("id"_L1);
    QCOMPARE(McpProtocolCallToolRequest::fromJson(missingId), McpProtocolCallToolRequest());

    QJsonObject invalidId = obj;
    invalidId["id"_L1] = true;
    QCOMPARE(McpProtocolCallToolRequest::fromJson(invalidId), McpProtocolCallToolRequest());

    QJsonObject missingParams = obj;
    missingParams.remove("params"_L1);
    QCOMPARE(McpProtocolCallToolRequest::fromJson(missingParams), McpProtocolCallToolRequest());

    QJsonObject invalidParams = obj;
    invalidParams["params"_L1] = QJsonObject();
    QCOMPARE(McpProtocolCallToolRequest::fromJson(invalidParams), McpProtocolCallToolRequest());
}

#include "moc_mcpprotocolcalltoolrequesttest.cpp"
