/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolcompleterequestparamstest.h"
#include "impl/mcpprotocolcompleterequestparams.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolCompleteRequestParamsTest)

McpProtocolCompleteRequestParamsTest::McpProtocolCompleteRequestParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolCompleteRequestParamsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolCompleteRequestParams w;
    QVERIFY(!w.meta().has_value());
    // TODO
}
void McpProtocolCompleteRequestParamsTest::shouldRejectMissingRequiredFields()
{
    using namespace Qt::Literals::StringLiterals;
    using namespace TextAutoGenerateTextMcpProtocolCore;
    QJsonObject ref;
    ref["type"_L1] = u"ref/prompt"_s;
    ref["name"_L1] = u"prompt"_s;
    QJsonObject argument;
    argument["name"_L1] = u"arg"_s;
    argument["value"_L1] = QString();
    QJsonObject obj;
    obj["ref"_L1] = ref;
    obj["argument"_L1] = argument;
    QVERIFY(McpProtocolCompleteRequestParams::fromJson(obj).isValid());

    QJsonObject missingRef = obj;
    missingRef.remove("ref"_L1);
    QCOMPARE(McpProtocolCompleteRequestParams::fromJson(missingRef), McpProtocolCompleteRequestParams());

    QJsonObject unknownRef = obj;
    QJsonObject badRef = ref;
    badRef["type"_L1] = u"ref/foo"_s;
    unknownRef["ref"_L1] = badRef;
    QCOMPARE(McpProtocolCompleteRequestParams::fromJson(unknownRef), McpProtocolCompleteRequestParams());

    QJsonObject missingArgument = obj;
    missingArgument.remove("argument"_L1);
    QCOMPARE(McpProtocolCompleteRequestParams::fromJson(missingArgument), McpProtocolCompleteRequestParams());

    QJsonObject missingArgumentValue = obj;
    QJsonObject badArgument = argument;
    badArgument.remove("value"_L1);
    missingArgumentValue["argument"_L1] = badArgument;
    QCOMPARE(McpProtocolCompleteRequestParams::fromJson(missingArgumentValue), McpProtocolCompleteRequestParams());
}

#include "moc_mcpprotocolcompleterequestparamstest.cpp"
