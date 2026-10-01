/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolresulttest.h"
#include "impl/mcpprotocolresult.h"
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolResultTest)

McpProtocolResultTest::McpProtocolResultTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolResultTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolResult w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(w.additionalProperties().isEmpty());
}

void McpProtocolResultTest::shouldLoadAndSaveMetaAndAdditionalProperties()
{
    QJsonObject meta;
    meta["progressToken"_L1] = u"token"_s;
    meta["foo"_L1] = 12;
    QJsonObject obj;
    obj["_meta"_L1] = meta;
    obj["extra"_L1] = u"value"_s;
    obj["other"_L1] = true;

    const auto result = TextAutoGenerateTextMcpProtocolCore::McpProtocolResult::fromJson(obj);
    QVERIFY(result.meta().has_value());
    QVERIFY(result.meta()->meta().has_value());
    QCOMPARE(result.meta()->meta()->value(u"progressToken"_s), QJsonValue(u"token"_s));
    QCOMPARE(result.additionalProperties().count(), 2);

    const QJsonObject saved = TextAutoGenerateTextMcpProtocolCore::McpProtocolResult::toJson(result);
    QCOMPARE(saved, obj);
    QCOMPARE(saved.value("_meta"_L1).toObject(), meta);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolResult::fromJson(saved), result);
}

#include "moc_mcpprotocolresulttest.cpp"
