/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolsubscriptionslistenrequestparamstest.h"
#include "impl/mcpprotocolsubscriptionslistenrequestparams.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolSubscriptionsListenRequestParamsTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSubscriptionsListenRequestParamsTest::McpProtocolSubscriptionsListenRequestParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolSubscriptionsListenRequestParamsTest::shouldHaveDefaultValues()
{
    const McpProtocolSubscriptionsListenRequestParams w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.notifications().has_value());
    QVERIFY(!w.isValid());
}

void McpProtocolSubscriptionsListenRequestParamsTest::shouldConvertJson()
{
    const QJsonObject obj{{"_meta"_L1, QJsonObject{{"progressToken"_L1, u"tok"_s}}}, {"notifications"_L1, QJsonObject{{"toolsListChanged"_L1, true}}}};
    const McpProtocolSubscriptionsListenRequestParams params = McpProtocolSubscriptionsListenRequestParams::fromJson(obj);
    QVERIFY(params.isValid());
    QVERIFY(params.meta().has_value());
    QCOMPARE(params.notifications()->toolsListChanged(), true);
    QCOMPARE(McpProtocolSubscriptionsListenRequestParams::toJson(params), obj);

    // An empty filter is valid
    const QJsonObject emptyFilter{{"notifications"_L1, QJsonObject()}};
    const McpProtocolSubscriptionsListenRequestParams emptyParams = McpProtocolSubscriptionsListenRequestParams::fromJson(emptyFilter);
    QVERIFY(emptyParams.isValid());
    QCOMPARE(McpProtocolSubscriptionsListenRequestParams::toJson(emptyParams), emptyFilter);
}

void McpProtocolSubscriptionsListenRequestParamsTest::shouldRejectMissingRequiredFields()
{
    QVERIFY(!McpProtocolSubscriptionsListenRequestParams::fromJson(QJsonObject()).isValid());
    const QJsonObject obj{{"notifications"_L1, true}};
    QCOMPARE(McpProtocolSubscriptionsListenRequestParams::fromJson(obj), McpProtocolSubscriptionsListenRequestParams());
}

#include "moc_mcpprotocolsubscriptionslistenrequestparamstest.cpp"
