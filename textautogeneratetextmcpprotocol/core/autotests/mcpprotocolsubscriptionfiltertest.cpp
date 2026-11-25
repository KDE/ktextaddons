/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolsubscriptionfiltertest.h"
#include "impl/mcpprotocolsubscriptionfilter.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolSubscriptionFilterTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSubscriptionFilterTest::McpProtocolSubscriptionFilterTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolSubscriptionFilterTest::shouldHaveDefaultValues()
{
    const McpProtocolSubscriptionFilter w;
    QVERIFY(!w.toolsListChanged().has_value());
    QVERIFY(!w.promptsListChanged().has_value());
    QVERIFY(!w.resourcesListChanged().has_value());
    QVERIFY(!w.resourceSubscriptions().has_value());
    QCOMPARE(McpProtocolSubscriptionFilter::toJson(w), QJsonObject());
}

void McpProtocolSubscriptionFilterTest::shouldConvertJson()
{
    const QJsonObject obj{{"toolsListChanged"_L1, true},
                          {"promptsListChanged"_L1, false},
                          {"resourcesListChanged"_L1, true},
                          {"resourceSubscriptions"_L1, QJsonArray{u"file:///a.txt"_s, u"file:///b.txt"_s}}};
    const McpProtocolSubscriptionFilter filter = McpProtocolSubscriptionFilter::fromJson(obj);
    QCOMPARE(filter.toolsListChanged(), true);
    QCOMPARE(filter.promptsListChanged(), false);
    QCOMPARE(filter.resourcesListChanged(), true);
    QCOMPARE(filter.resourceSubscriptions(), QStringList({u"file:///a.txt"_s, u"file:///b.txt"_s}));
    QCOMPARE(McpProtocolSubscriptionFilter::toJson(filter), obj);

    const QJsonObject partial{{"toolsListChanged"_L1, true}};
    QCOMPARE(McpProtocolSubscriptionFilter::toJson(McpProtocolSubscriptionFilter::fromJson(partial)), partial);
}

void McpProtocolSubscriptionFilterTest::shouldRejectMissingRequiredFields()
{
    // No required field, but resourceSubscriptions must only contain strings
    const QJsonObject obj{{"toolsListChanged"_L1, true}, {"resourceSubscriptions"_L1, QJsonArray{u"file:///a.txt"_s, 42}}};
    QCOMPARE(McpProtocolSubscriptionFilter::fromJson(obj), McpProtocolSubscriptionFilter());
}

#include "moc_mcpprotocolsubscriptionfiltertest.cpp"
