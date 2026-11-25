/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolsubscriptionslistenresulttest.h"
#include "impl/mcpprotocolsubscriptionslistenresult.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolSubscriptionsListenResultTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSubscriptionsListenResultTest::McpProtocolSubscriptionsListenResultTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolSubscriptionsListenResultTest::shouldHaveDefaultValues()
{
    const McpProtocolSubscriptionsListenResult w;
    QVERIFY(!w.isValid());
    QVERIFY(!w.meta().subscriptionId().has_value());
}

void McpProtocolSubscriptionsListenResultTest::shouldConvertJson()
{
    const QJsonObject obj{{"_meta"_L1, QJsonObject{{"io.modelcontextprotocol/subscriptionId"_L1, u"abc"_s}}}};
    const McpProtocolSubscriptionsListenResult result = McpProtocolSubscriptionsListenResult::fromJson(obj);
    QVERIFY(result.isValid());
    QCOMPARE(result.meta().subscriptionId(), McpProtocolUtils::RequestId(u"abc"_s));
    QCOMPARE(McpProtocolSubscriptionsListenResult::toJson(result), obj);
}

void McpProtocolSubscriptionsListenResultTest::shouldRejectMissingRequiredFields()
{
    QCOMPARE(McpProtocolSubscriptionsListenResult::fromJson(QJsonObject()), McpProtocolSubscriptionsListenResult());
    const QJsonObject obj{{"_meta"_L1, QJsonObject()}};
    QCOMPARE(McpProtocolSubscriptionsListenResult::fromJson(obj), McpProtocolSubscriptionsListenResult());
}

#include "moc_mcpprotocolsubscriptionslistenresulttest.cpp"
