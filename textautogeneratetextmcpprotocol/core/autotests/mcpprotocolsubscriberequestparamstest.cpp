/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolsubscriberequestparamstest.h"
#include "impl/mcpprotocolsubscriberequestparams.h"
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolSubscribeRequestParamsTest)

McpProtocolSubscribeRequestParamsTest::McpProtocolSubscribeRequestParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolSubscribeRequestParamsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscribeRequestParams w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(w.uri().isEmpty());
}

void McpProtocolSubscribeRequestParamsTest::shouldRejectMissingRequiredFields()
{
    using namespace TextAutoGenerateTextMcpProtocolCore;
    QVERIFY(McpProtocolSubscribeRequestParams::fromJson(QJsonObject{{"uri"_L1, u"file:///foo"_s}}).isValid());
    // Missing uri
    QCOMPARE(McpProtocolSubscribeRequestParams::fromJson(QJsonObject()), McpProtocolSubscribeRequestParams());
    // uri is not a string
    QCOMPARE(McpProtocolSubscribeRequestParams::fromJson(QJsonObject{{"uri"_L1, 2}}), McpProtocolSubscribeRequestParams());
}

#include "moc_mcpprotocolsubscriberequestparamstest.cpp"
