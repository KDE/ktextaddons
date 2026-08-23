/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoltitledsingleselectenumschematest.h"
#include "impl/mcpprotocoltitledsingleselectenumschema.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolTitledSingleSelectEnumSchemaTest)
using namespace Qt::Literals::StringLiterals;

McpProtocolTitledSingleSelectEnumSchemaTest::McpProtocolTitledSingleSelectEnumSchemaTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolTitledSingleSelectEnumSchemaTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolTitledSingleSelectEnumSchema w;
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolTitledSingleSelectEnumSchema::type(), "string");
    QVERIFY(!w.description().has_value());
    QVERIFY(!w.title().has_value());
    QVERIFY(!w.defaultValue().has_value());
    QVERIFY(w.oneOf().isEmpty());
}

void McpProtocolTitledSingleSelectEnumSchemaTest::shouldConvertJson()
{
    QJsonObject firstItem;
    firstItem["const"_L1] = u"red"_s;
    firstItem["title"_L1] = u"Red"_s;
    QJsonObject secondItem;
    secondItem["const"_L1] = u"blue"_s;
    secondItem["title"_L1] = u"Blue"_s;

    QJsonObject obj;
    obj["type"_L1] = u"string"_s;
    obj["oneOf"_L1] = QJsonArray{firstItem, secondItem};
    obj["default"_L1] = u"red"_s;
    obj["description"_L1] = u"A color"_s;
    obj["title"_L1] = u"Color"_s;

    const auto schema = TextAutoGenerateTextMcpProtocolCore::McpProtocolTitledSingleSelectEnumSchema::fromJson(obj);
    QCOMPARE(schema.oneOf().count(), 2);
    QCOMPARE(schema.oneOf().at(0).constValue(), u"red"_s);
    QCOMPARE(schema.oneOf().at(0).title(), u"Red"_s);
    QCOMPARE(schema.oneOf().at(1).constValue(), u"blue"_s);
    QCOMPARE(schema.oneOf().at(1).title(), u"Blue"_s);
    QCOMPARE(schema.defaultValue(), u"red"_s);
    QCOMPARE(schema.description(), u"A color"_s);
    QCOMPARE(schema.title(), u"Color"_s);

    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolTitledSingleSelectEnumSchema::toJson(schema), obj);
}

#include "moc_mcpprotocoltitledsingleselectenumschematest.cpp"
