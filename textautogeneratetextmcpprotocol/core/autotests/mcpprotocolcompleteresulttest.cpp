/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolcompleteresulttest.h"
#include "impl/mcpprotocolcompleteresult.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolCompleteResultTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolCompleteResultTest::McpProtocolCompleteResultTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolCompleteResultTest::shouldHaveDefaultValues()
{
    const McpProtocolCompleteResult w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(w.completion().values().isEmpty());
    QVERIFY(!w.completion().hasMore().has_value());
    QVERIFY(!w.completion().total().has_value());
}

void McpProtocolCompleteResultTest::shouldConvertJson()
{
    QJsonObject completion;
    completion["values"_L1] = QJsonArray{u"foo"_s, u"bar"_s};
    completion["hasMore"_L1] = true;
    completion["total"_L1] = 12;

    QJsonObject obj;
    obj["completion"_L1] = completion;

    const auto result = McpProtocolCompleteResult::fromJson(obj);
    QCOMPARE(result.completion().values(), QStringList({u"foo"_s, u"bar"_s}));
    QCOMPARE(result.completion().hasMore(), true);
    QCOMPARE(result.completion().total(), 12);
    QCOMPARE(McpProtocolCompleteResult::toJson(result), obj);
}

void McpProtocolCompleteResultTest::shouldRejectMissingRequiredFields()
{
    using namespace Qt::Literals::StringLiterals;
    using namespace TextAutoGenerateTextMcpProtocolCore;
    QCOMPARE(McpProtocolCompleteResult::fromJson(QJsonObject()), McpProtocolCompleteResult());

    QJsonObject meta;
    meta["foo"_L1] = u"bar"_s;
    QJsonObject obj;
    obj["_meta"_L1] = meta;
    obj["completion"_L1] = QJsonObject();
    QCOMPARE(McpProtocolCompleteResult::fromJson(obj), McpProtocolCompleteResult());

    QJsonObject completion;
    completion["values"_L1] = u"foo"_s;
    obj["completion"_L1] = completion;
    QCOMPARE(McpProtocolCompleteResult::fromJson(obj), McpProtocolCompleteResult());

    completion["values"_L1] = QJsonArray();
    obj["completion"_L1] = completion;
    QVERIFY(McpProtocolCompleteResult::fromJson(obj).meta().has_value());
}

#include "moc_mcpprotocolcompleteresulttest.cpp"
