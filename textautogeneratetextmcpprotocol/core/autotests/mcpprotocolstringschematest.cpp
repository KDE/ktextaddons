/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolstringschematest.h"
#include "impl/mcpprotocolstringschema.h"
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolStringSchemaTest)

McpProtocolStringSchemaTest::McpProtocolStringSchemaTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolStringSchemaTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolStringSchema w;
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolStringSchema::type(), "string");
    QVERIFY(!w.description().has_value());
    QVERIFY(!w.title().has_value());
    QVERIFY(!w.defaultValue().has_value());
    QVERIFY(!w.format().has_value());
    QVERIFY(!w.minLength().has_value());
    QVERIFY(!w.maxLength().has_value());
}

void McpProtocolStringSchemaTest::shouldLoadAndSaveStringSchema()
{
    QJsonObject obj;
    obj["type"_L1] = u"string"_s;
    obj["format"_L1] = u"date-time"_s;
    obj["default"_L1] = u"2025-01-01T00:00:00Z"_s;
    obj["title"_L1] = u"Date"_s;
    obj["minLength"_L1] = 2;
    obj["maxLength"_L1] = 40;

    const auto schema = TextAutoGenerateTextMcpProtocolCore::McpProtocolStringSchema::fromJson(obj);
    QCOMPARE(*schema.format(), TextAutoGenerateTextMcpProtocolCore::McpProtocolStringSchema::Format::DateTime);
    QCOMPARE(*schema.defaultValue(), u"2025-01-01T00:00:00Z"_s);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolStringSchema::toJson(schema), obj);

    TextAutoGenerateTextMcpProtocolCore::McpProtocolStringSchema unknownFormat;
    unknownFormat.setFormat(TextAutoGenerateTextMcpProtocolCore::McpProtocolStringSchema::Format::Unknown);
    QVERIFY(!TextAutoGenerateTextMcpProtocolCore::McpProtocolStringSchema::toJson(unknownFormat).contains("format"_L1));
}

#include "moc_mcpprotocolstringschematest.cpp"
