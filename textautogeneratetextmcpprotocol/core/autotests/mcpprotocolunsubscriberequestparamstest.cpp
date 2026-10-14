/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolunsubscriberequestparamstest.h"
#include "impl/mcpprotocolunsubscriberequestparams.h"
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolUnsubscribeRequestParamsTest)

McpProtocolUnsubscribeRequestParamsTest::McpProtocolUnsubscribeRequestParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolUnsubscribeRequestParamsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolUnsubscribeRequestParams w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(w.uri().isEmpty());
}

void McpProtocolUnsubscribeRequestParamsTest::shouldRejectMissingRequiredFields()
{
    using namespace TextAutoGenerateTextMcpProtocolCore;
    QVERIFY(McpProtocolUnsubscribeRequestParams::fromJson(QJsonObject{{"uri"_L1, u"file:///foo"_s}}).isValid());
    // Missing uri
    QCOMPARE(McpProtocolUnsubscribeRequestParams::fromJson(QJsonObject()), McpProtocolUnsubscribeRequestParams());
    // uri is not a string
    QCOMPARE(McpProtocolUnsubscribeRequestParams::fromJson(QJsonObject{{"uri"_L1, 2}}), McpProtocolUnsubscribeRequestParams());
}

#include "moc_mcpprotocolunsubscriberequestparamstest.cpp"
