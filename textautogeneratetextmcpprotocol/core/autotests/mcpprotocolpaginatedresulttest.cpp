/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolpaginatedresulttest.h"
#include "impl/mcpprotocolpaginatedresult.h"
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolPaginatedResultTest)

McpProtocolPaginatedResultTest::McpProtocolPaginatedResultTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolPaginatedResultTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolPaginatedResult w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.nextCursor().has_value());
}

void McpProtocolPaginatedResultTest::shouldParseNextCursor_data()
{
    QTest::addColumn<QJsonObject>("obj");
    QTest::addColumn<std::optional<QString>>("expected");

    QTest::newRow("absent") << QJsonObject{} << std::optional<QString>{};
    QTest::newRow("string") << QJsonObject{{"nextCursor"_L1, u"c1"_s}} << std::optional<QString>{u"c1"_s};
    // Empty string is a valid opaque cursor
    QTest::newRow("empty-string") << QJsonObject{{"nextCursor"_L1, QString()}} << std::optional<QString>{QString()};
    QTest::newRow("null") << QJsonObject{{"nextCursor"_L1, QJsonValue::Null}} << std::optional<QString>{};
    QTest::newRow("number") << QJsonObject{{"nextCursor"_L1, 42}} << std::optional<QString>{};
}

void McpProtocolPaginatedResultTest::shouldParseNextCursor()
{
    QFETCH(QJsonObject, obj);
    QFETCH(std::optional<QString>, expected);
    const auto result = TextAutoGenerateTextMcpProtocolCore::McpProtocolPaginatedResult::fromJson(obj);
    QCOMPARE(result.nextCursor(), expected);
}

#include "moc_mcpprotocolpaginatedresulttest.cpp"
