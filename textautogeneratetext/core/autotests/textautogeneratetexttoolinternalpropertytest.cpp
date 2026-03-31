/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetexttoolinternalpropertytest.h"
#include "core/tools/textautogeneratetexttoolinternalproperty.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateTextToolInternalPropertyTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTextToolInternalPropertyTest::TextAutoGenerateTextToolInternalPropertyTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextToolInternalPropertyTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty w;
    QVERIFY(w.typeElements().isEmpty());
    QVERIFY(w.description().isEmpty());
    QVERIFY(w.name().isEmpty());
    QVERIFY(!w.isValid());
    QCOMPARE(w.propertyType(), TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty::PropertyType::String);
}

void TextAutoGenerateTextToolInternalPropertyTest::shouldConvertPropertyType()
{
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty::convertPropertyTypeFromString(u"string"_s),
             TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty::PropertyType::String);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty::convertPropertyTypeFromString(u"boolean"_s),
             TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty::PropertyType::Boolean);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty::convertPropertyTypeFromString(u"integer"_s),
             TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty::PropertyType::Integer);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty::convertPropertyTypeFromString(u"number"_s),
             TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty::PropertyType::Number);

    QCOMPARE(TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty::convertPropertyTypeToString(
                 TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty::PropertyType::String),
             u"string"_s);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty::convertPropertyTypeToString(
                 TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty::PropertyType::Boolean),
             u"boolean"_s);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty::convertPropertyTypeToString(
                 TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty::PropertyType::Integer),
             u"integer"_s);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty::convertPropertyTypeToString(
                 TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty::PropertyType::Number),
             u"number"_s);
}

#include "moc_textautogeneratetexttoolinternalpropertytest.cpp"
