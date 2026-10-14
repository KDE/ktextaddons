/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolsetlevelrequesttest.h"
#include "impl/mcpprotocolsetlevelrequest.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolSetLevelRequestTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolSetLevelRequestTest::McpProtocolSetLevelRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolSetLevelRequestTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolSetLevelRequest w;
    QCOMPARE(w.type(), "logging/setLevel"_ba);
    // TODO
}

void McpProtocolSetLevelRequestTest::shouldRejectMissingRequiredFields()
{
    using namespace TextAutoGenerateTextMcpProtocolCore;
    const QJsonObject obj{{"jsonrpc"_L1, u"2.0"_s}, {"method"_L1, u"logging/setLevel"_s}, {"id"_L1, 1}, {"params"_L1, QJsonObject{{"level"_L1, u"info"_s}}}};
    const McpProtocolSetLevelRequest request = McpProtocolSetLevelRequest::fromJson(obj);
    QCOMPARE(request.params().level(), McpProtocolUtils::LoggingLevel::Info);
    QCOMPARE(McpProtocolSetLevelRequest::toJson(request), obj);

    // Missing id
    QJsonObject withoutId = obj;
    withoutId.remove("id"_L1);
    QCOMPARE(McpProtocolSetLevelRequest::fromJson(withoutId), McpProtocolSetLevelRequest());
    // Invalid id
    QJsonObject invalidId = obj;
    invalidId["id"_L1] = true;
    QCOMPARE(McpProtocolSetLevelRequest::fromJson(invalidId), McpProtocolSetLevelRequest());
    // Missing params
    QJsonObject withoutParams = obj;
    withoutParams.remove("params"_L1);
    QCOMPARE(McpProtocolSetLevelRequest::fromJson(withoutParams), McpProtocolSetLevelRequest());
    // Params without level
    QJsonObject withoutLevel = obj;
    withoutLevel["params"_L1] = QJsonObject();
    QCOMPARE(McpProtocolSetLevelRequest::fromJson(withoutLevel), McpProtocolSetLevelRequest());
}

#include "moc_mcpprotocolsetlevelrequesttest.cpp"
