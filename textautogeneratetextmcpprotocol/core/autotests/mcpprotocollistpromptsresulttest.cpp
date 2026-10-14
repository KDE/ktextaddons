/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocollistpromptsresulttest.h"
#include "impl/mcpprotocollistpromptsresult.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolListPromptsResultTest)

McpProtocolListPromptsResultTest::McpProtocolListPromptsResultTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolListPromptsResultTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolListPromptsResult w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.nextCursor().has_value());
    QVERIFY(!w.meta().has_value());
    QVERIFY(w.prompts().isEmpty());
}

void McpProtocolListPromptsResultTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolListPromptsResult;
    using namespace Qt::Literals::StringLiterals;
    QJsonObject validItem;
    validItem["name"_L1] = u"prompt"_s;
    QJsonObject valid;
    valid["prompts"_L1] = QJsonArray{validItem, QJsonObject()};
    const McpProtocolListPromptsResult result = McpProtocolListPromptsResult::fromJson(valid);
    // Invalid item is skipped
    QCOMPARE(result.prompts().count(), 1);

    QJsonObject obj = valid;
    obj.remove(u"prompts"_s);
    QCOMPARE(McpProtocolListPromptsResult::fromJson(obj), McpProtocolListPromptsResult());
}

#include "moc_mcpprotocollistpromptsresulttest.cpp"
