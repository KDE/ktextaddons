/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolmetatest.h"
#include "impl/mcpprotocolmeta.h"
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolMetaTest)

McpProtocolMetaTest::McpProtocolMetaTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolMetaTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolMeta w;
    QVERIFY(!w.meta().has_value());
}

void McpProtocolMetaTest::shouldLoadAndSaveMeta()
{
    QJsonObject metaObj;
    metaObj["progressToken"_L1] = u"abc"_s;
    metaObj["io.modelcontextprotocol/related-task"_L1] = QJsonObject{{"taskId"_L1, u"t1"_s}};
    metaObj["count"_L1] = 3;

    const auto meta = TextAutoGenerateTextMcpProtocolCore::McpProtocolMeta::fromJson(metaObj);
    QVERIFY(meta.meta().has_value());
    QCOMPARE(meta.meta()->count(), 3);
    QCOMPARE(meta.meta()->value(u"progressToken"_s), QJsonValue(u"abc"_s));
    QCOMPARE(meta.meta()->value(u"count"_s), QJsonValue(3));

    const QJsonObject saved = TextAutoGenerateTextMcpProtocolCore::McpProtocolMeta::toJson(meta);
    QCOMPARE(saved, metaObj);
    QVERIFY(!saved.contains("_meta"_L1));
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolMeta::fromJson(saved), meta);
}
#include "moc_mcpprotocolmetatest.cpp"
