/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetexttoolpluginpropertytest.h"
#include "core/tools/textautogeneratetexttoolpluginproperty.h"
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(TextAutoGenerateTextToolPluginPropertyTest)
TextAutoGenerateTextToolPluginPropertyTest::TextAutoGenerateTextToolPluginPropertyTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextToolPluginPropertyTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty w;
    QVERIFY(w.description().isEmpty());
    QVERIFY(w.name().isEmpty());
    QVERIFY(w.typeElements().isEmpty());
    QCOMPARE(w.propertyType(), TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty::PropertyType::String);
}

void TextAutoGenerateTextToolPluginPropertyTest::shouldConvertPropertyType()
{
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty::convertPropertyTypeFromString(u"string"_s),
             TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty::PropertyType::String);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty::convertPropertyTypeFromString(u"boolean"_s),
             TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty::PropertyType::Boolean);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty::convertPropertyTypeFromString(u"integer"_s),
             TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty::PropertyType::Integer);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty::convertPropertyTypeFromString(u"number"_s),
             TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty::PropertyType::Number);

    QCOMPARE(TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty::convertPropertyTypeToString(
                 TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty::PropertyType::String),
             u"string"_s);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty::convertPropertyTypeToString(
                 TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty::PropertyType::Boolean),
             u"boolean"_s);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty::convertPropertyTypeToString(
                 TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty::PropertyType::Integer),
             u"integer"_s);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty::convertPropertyTypeToString(
                 TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty::PropertyType::Number),
             u"number"_s);
}
#include "moc_textautogeneratetexttoolpluginpropertytest.cpp"
