/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolsetlevelrequestparamstest.h"
#include "impl/mcpprotocolsetlevelrequestparams.h"
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolSetLevelRequestParamsTest)

McpProtocolSetLevelRequestParamsTest::McpProtocolSetLevelRequestParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolSetLevelRequestParamsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolSetLevelRequestParams w;
    QVERIFY(!w.meta().has_value());
    QCOMPARE(w.level(), TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel::Unknown);
}

void McpProtocolSetLevelRequestParamsTest::shouldRejectMissingRequiredFields()
{
    using namespace TextAutoGenerateTextMcpProtocolCore;
    const McpProtocolSetLevelRequestParams params = McpProtocolSetLevelRequestParams::fromJson(QJsonObject{{"level"_L1, u"error"_s}});
    QVERIFY(params.isValid());
    QCOMPARE(params.level(), McpProtocolUtils::LoggingLevel::Error);
    // Missing level
    QCOMPARE(McpProtocolSetLevelRequestParams::fromJson(QJsonObject()), McpProtocolSetLevelRequestParams());
    // Unknown level
    QCOMPARE(McpProtocolSetLevelRequestParams::fromJson(QJsonObject{{"level"_L1, u"foo"_s}}), McpProtocolSetLevelRequestParams());
    // Level is not a string
    QCOMPARE(McpProtocolSetLevelRequestParams::fromJson(QJsonObject{{"level"_L1, 3}}), McpProtocolSetLevelRequestParams());
}

#include "moc_mcpprotocolsetlevelrequestparamstest.cpp"
