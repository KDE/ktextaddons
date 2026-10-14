/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolcalltoolresulttest.h"
#include "impl/mcpprotocolcalltoolresult.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolCallToolResultTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolCallToolResultTest::McpProtocolCallToolResultTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolCallToolResultTest::shouldHaveDefaultValues()
{
    const McpProtocolCallToolResult w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.isError().has_value());
    QVERIFY(!w.structuredContent().has_value());
    QVERIFY(w.content().isEmpty());
}

void McpProtocolCallToolResultTest::shouldConvertJson()
{
    QJsonObject textContent;
    textContent["type"_L1] = u"text"_s;
    textContent["text"_L1] = u"Hello"_s;
    QJsonObject linkContent;
    linkContent["type"_L1] = u"resource_link"_s;
    linkContent["name"_L1] = u"file"_s;
    linkContent["uri"_L1] = u"file:///tmp/foo"_s;

    QJsonObject obj;
    obj["content"_L1] = QJsonArray{textContent, linkContent};
    obj["isError"_L1] = false;

    const auto result = McpProtocolCallToolResult::fromJson(obj);
    QCOMPARE(result.isError(), false);
    QCOMPARE(result.content().count(), 2);
    const auto first = std::get_if<McpProtocolTextContent>(&result.content().at(0));
    QVERIFY(first);
    QCOMPARE(first->text(), u"Hello"_s);
    QVERIFY(std::holds_alternative<McpProtocolResourceLink>(result.content().at(1)));

    QCOMPARE(McpProtocolCallToolResult::toJson(result), obj);
}

void McpProtocolCallToolResultTest::shouldIgnoreUnknownContent()
{
    QJsonObject textContent;
    textContent["type"_L1] = u"text"_s;
    textContent["text"_L1] = u"Hello"_s;
    QJsonObject unknownContent;
    unknownContent["type"_L1] = u"video"_s;

    QJsonObject obj;
    obj["content"_L1] = QJsonArray{unknownContent, textContent};
    const auto result = McpProtocolCallToolResult::fromJson(obj);
    // Unknown content must not become an empty text content
    QCOMPARE(result.content().count(), 1);
    const auto first = std::get_if<McpProtocolTextContent>(&result.content().at(0));
    QVERIFY(first);
    QCOMPARE(first->text(), u"Hello"_s);
}

void McpProtocolCallToolResultTest::shouldRejectMissingRequiredFields()
{
    QCOMPARE(McpProtocolCallToolResult::fromJson(QJsonObject()), McpProtocolCallToolResult());

    QJsonObject obj;
    obj["content"_L1] = u"foo"_s;
    obj["isError"_L1] = true;
    QCOMPARE(McpProtocolCallToolResult::fromJson(obj), McpProtocolCallToolResult());

    obj["content"_L1] = QJsonArray();
    QCOMPARE(McpProtocolCallToolResult::fromJson(obj).isError(), true);
}

void McpProtocolCallToolResultTest::shouldIgnoreInvalidContent()
{
    // Rejected content must not become an empty content
    const QJsonObject resourceLinkWithoutUri{{"type"_L1, u"resource_link"_s}, {"name"_L1, u"foo"_s}};
    const QJsonObject imageWithoutData{{"type"_L1, u"image"_s}, {"mimeType"_L1, u"image/png"_s}};
    const QJsonObject embeddedResourceWithoutUri{{"type"_L1, u"resource"_s}, {"resource"_L1, QJsonObject{{"text"_L1, u"foo"_s}}}};
    const QJsonObject textContent{{"type"_L1, u"text"_s}, {"text"_L1, u"Hello"_s}};

    QJsonObject obj;
    obj["content"_L1] = QJsonArray{resourceLinkWithoutUri, imageWithoutData, embeddedResourceWithoutUri, textContent};
    const auto result = McpProtocolCallToolResult::fromJson(obj);
    QCOMPARE(result.content().count(), 1);
    QVERIFY(std::holds_alternative<McpProtocolTextContent>(result.content().at(0)));
}

#include "moc_mcpprotocolcalltoolresulttest.cpp"
