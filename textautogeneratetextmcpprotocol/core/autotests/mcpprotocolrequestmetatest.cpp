/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolrequestmetatest.h"
#include "impl/mcpprotocolrequestmeta.h"
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
QTEST_GUILESS_MAIN(McpProtocolRequestMetaTest)

McpProtocolRequestMetaTest::McpProtocolRequestMetaTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolRequestMetaTest::shouldHaveDefaultValues()
{
    const McpProtocolRequestMeta w;
    QVERIFY(!w.progressToken().has_value());
    QVERIFY(w.additionalProperties().isEmpty());
    QVERIFY(McpProtocolRequestMeta::toJson(w).isEmpty());
}

void McpProtocolRequestMetaTest::shouldLoadAndSaveMeta()
{
    const QJsonObject obj{{"progressToken"_L1, u"token-1"_s}, {"io.modelcontextprotocol/related-task"_L1, QJsonObject{{"taskId"_L1, u"t1"_s}}}};
    const McpProtocolRequestMeta meta = McpProtocolRequestMeta::fromJson(obj);
    QCOMPARE(meta.progressToken(), McpProtocolUtils::ProgressToken(u"token-1"_s));
    QCOMPARE(meta.additionalProperties().count(), 1);
    QVERIFY(!meta.additionalProperties().contains("progressToken"_L1));
    QCOMPARE(McpProtocolRequestMeta::toJson(meta), obj);
    QCOMPARE(McpProtocolRequestMeta::fromJson(McpProtocolRequestMeta::toJson(meta)), meta);

    const McpProtocolRequestMeta numberToken = McpProtocolRequestMeta::fromJson(QJsonObject{{"progressToken"_L1, 4}});
    QCOMPARE(numberToken.progressToken(), McpProtocolUtils::ProgressToken(qint64(4)));
}

void McpProtocolRequestMetaTest::shouldKeepInvalidProgressToken()
{
    // Invalid token is not converted to an empty token: it's saved again as is
    const QJsonObject obj{{"progressToken"_L1, QJsonValue::Null}};
    const McpProtocolRequestMeta meta = McpProtocolRequestMeta::fromJson(obj);
    QVERIFY(!meta.progressToken().has_value());
    QCOMPARE(McpProtocolRequestMeta::toJson(meta), obj);
}

#include "moc_mcpprotocolrequestmetatest.cpp"
