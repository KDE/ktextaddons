/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocollistresourcesresulttest.h"
#include "impl/mcpprotocollistresourcesresult.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolListResourcesResultTest)

McpProtocolListResourcesResultTest::McpProtocolListResourcesResultTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolListResourcesResultTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolListResourcesResult w;
    QVERIFY(!w.nextCursor().has_value());
    QVERIFY(!w.meta().has_value());
}

void McpProtocolListResourcesResultTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolListResourcesResult;
    using namespace Qt::Literals::StringLiterals;
    QJsonObject validItem;
    validItem["name"_L1] = u"resource"_s;
    validItem["uri"_L1] = u"file:///tmp/a.txt"_s;
    QJsonObject valid;
    valid["resources"_L1] = QJsonArray{validItem, QJsonObject()};
    const McpProtocolListResourcesResult result = McpProtocolListResourcesResult::fromJson(valid);
    // Invalid item is skipped
    QCOMPARE(result.resources().count(), 1);

    QJsonObject obj = valid;
    obj.remove(u"resources"_s);
    QCOMPARE(McpProtocolListResourcesResult::fromJson(obj), McpProtocolListResourcesResult());
}

#include "moc_mcpprotocollistresourcesresulttest.cpp"
