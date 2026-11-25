/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolsubscriptionslistenresultmetaobjecttest.h"
#include "impl/mcpprotocolsubscriptionslistenresultmetaobject.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolSubscriptionsListenResultMetaObjectTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSubscriptionsListenResultMetaObjectTest::McpProtocolSubscriptionsListenResultMetaObjectTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolSubscriptionsListenResultMetaObjectTest::shouldHaveDefaultValues()
{
    const McpProtocolSubscriptionsListenResultMetaObject w;
    QVERIFY(!w.subscriptionId().has_value());
    QVERIFY(!w.serverInfo().has_value());
    QVERIFY(!w.isValid());
}

void McpProtocolSubscriptionsListenResultMetaObjectTest::shouldConvertJson()
{
    const QJsonObject obj{{"io.modelcontextprotocol/subscriptionId"_L1, 7},
                          {"io.modelcontextprotocol/serverInfo"_L1, QJsonObject{{"name"_L1, u"server"_s}, {"version"_L1, u"1.0"_s}}}};
    const McpProtocolSubscriptionsListenResultMetaObject meta = McpProtocolSubscriptionsListenResultMetaObject::fromJson(obj);
    QVERIFY(meta.isValid());
    QCOMPARE(meta.subscriptionId(), McpProtocolUtils::RequestId(qint64(7)));
    QCOMPARE(meta.serverInfo()->name(), u"server"_s);
    QCOMPARE(McpProtocolSubscriptionsListenResultMetaObject::toJson(meta), obj);

    const QJsonObject stringId{{"io.modelcontextprotocol/subscriptionId"_L1, u"sub-1"_s}};
    const McpProtocolSubscriptionsListenResultMetaObject metaStringId = McpProtocolSubscriptionsListenResultMetaObject::fromJson(stringId);
    QCOMPARE(metaStringId.subscriptionId(), McpProtocolUtils::RequestId(u"sub-1"_s));
    QCOMPARE(McpProtocolSubscriptionsListenResultMetaObject::toJson(metaStringId), stringId);
}

void McpProtocolSubscriptionsListenResultMetaObjectTest::shouldRejectMissingRequiredFields()
{
    QVERIFY(!McpProtocolSubscriptionsListenResultMetaObject::fromJson(QJsonObject()).isValid());
    const QJsonObject obj{{"io.modelcontextprotocol/subscriptionId"_L1, QJsonObject()}};
    QCOMPARE(McpProtocolSubscriptionsListenResultMetaObject::fromJson(obj), McpProtocolSubscriptionsListenResultMetaObject());
}

#include "moc_mcpprotocolsubscriptionslistenresultmetaobjecttest.cpp"
