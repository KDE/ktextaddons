/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocollistresourcetemplatesresulttest.h"
#include "impl/mcpprotocollistresourcetemplatesresult.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolListResourceTemplatesResultTest)

McpProtocolListResourceTemplatesResultTest::McpProtocolListResourceTemplatesResultTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolListResourceTemplatesResultTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolListResourceTemplatesResult w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.nextCursor().has_value());
    QVERIFY(w.resourceTemplates().isEmpty());
}

void McpProtocolListResourceTemplatesResultTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolListResourceTemplatesResult;
    using namespace Qt::Literals::StringLiterals;
    QJsonObject validItem;
    validItem["name"_L1] = u"template"_s;
    validItem["uriTemplate"_L1] = u"file:///{path}"_s;
    QJsonObject valid;
    valid["resourceTemplates"_L1] = QJsonArray{validItem, QJsonObject()};
    const McpProtocolListResourceTemplatesResult result = McpProtocolListResourceTemplatesResult::fromJson(valid);
    // Invalid item is skipped
    QCOMPARE(result.resourceTemplates().count(), 1);

    QJsonObject obj = valid;
    obj.remove(u"resourceTemplates"_s);
    QCOMPARE(McpProtocolListResourceTemplatesResult::fromJson(obj), McpProtocolListResourceTemplatesResult());
}

#include "moc_mcpprotocollistresourcetemplatesresulttest.cpp"
