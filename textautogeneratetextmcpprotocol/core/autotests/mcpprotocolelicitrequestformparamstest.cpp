/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolelicitrequestformparamstest.h"
#include "impl/mcpprotocolelicitrequestformparams.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolElicitRequestFormParamsTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolElicitRequestFormParamsTest::McpProtocolElicitRequestFormParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolElicitRequestFormParamsTest::shouldHaveDefaultValues()
{
    const McpProtocolElicitRequestFormParams w;
    QCOMPARE(McpProtocolElicitRequestFormParams::mode(), "form"_ba);
    QVERIFY(!w.meta().has_value());
    QVERIFY(w.message().isEmpty());
    QVERIFY(!w.task().has_value());
    QVERIFY(w.requestedSchema().properties().isEmpty());
    QVERIFY(!w.requestedSchema().required().has_value());
}

void McpProtocolElicitRequestFormParamsTest::shouldConvertJson()
{
    // One property per PrimitiveSchemaDefinition alternative, so the dispatcher is exercised.
    QJsonObject stringSchema;
    stringSchema["type"_L1] = u"string"_s;
    QJsonObject numberSchema;
    numberSchema["type"_L1] = u"integer"_s;
    QJsonObject booleanSchema;
    booleanSchema["type"_L1] = u"boolean"_s;
    QJsonObject untitledSingleSelect;
    untitledSingleSelect["type"_L1] = u"string"_s;
    untitledSingleSelect["enum"_L1] = QJsonArray{u"a"_s, u"b"_s};
    QJsonObject titledSingleSelectOption;
    titledSingleSelectOption["const"_L1] = u"a"_s;
    titledSingleSelectOption["title"_L1] = u"A"_s;
    QJsonObject titledSingleSelect;
    titledSingleSelect["type"_L1] = u"string"_s;
    titledSingleSelect["oneOf"_L1] = QJsonArray{titledSingleSelectOption};

    QJsonObject properties;
    properties["aString"_L1] = stringSchema;
    properties["aNumber"_L1] = numberSchema;
    properties["aBoolean"_L1] = booleanSchema;
    properties["anUntitledSingleSelect"_L1] = untitledSingleSelect;
    properties["aTitledSingleSelect"_L1] = titledSingleSelect;

    QJsonObject requestedSchema;
    requestedSchema["type"_L1] = u"object"_s;
    requestedSchema["properties"_L1] = properties;
    requestedSchema["required"_L1] = QJsonArray{u"aString"_s};

    QJsonObject obj;
    obj["mode"_L1] = u"form"_s;
    obj["message"_L1] = u"Please fill this in"_s;
    obj["requestedSchema"_L1] = requestedSchema;

    const auto params = McpProtocolElicitRequestFormParams::fromJson(obj);
    QCOMPARE(params.message(), u"Please fill this in"_s);
    const auto schema = params.requestedSchema();
    QCOMPARE(schema.properties().count(), 5);
    QCOMPARE(schema.required(), QStringList({u"aString"_s}));
    QVERIFY(std::holds_alternative<McpProtocolStringSchema>(schema.properties().value(u"aString"_s)));
    QVERIFY(std::holds_alternative<McpProtocolNumberSchema>(schema.properties().value(u"aNumber"_s)));
    QVERIFY(std::holds_alternative<McpProtocolBooleanSchema>(schema.properties().value(u"aBoolean"_s)));
    QVERIFY(std::holds_alternative<McpProtocolUntitledSingleSelectEnumSchema>(schema.properties().value(u"anUntitledSingleSelect"_s)));
    QVERIFY(std::holds_alternative<McpProtocolTitledSingleSelectEnumSchema>(schema.properties().value(u"aTitledSingleSelect"_s)));

    QCOMPARE(McpProtocolElicitRequestFormParams::toJson(params), obj);
}

#include "moc_mcpprotocolelicitrequestformparamstest.cpp"
