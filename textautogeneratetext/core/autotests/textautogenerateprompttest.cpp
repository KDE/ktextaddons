/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateprompttest.h"
#include "core/prompts/textautogenerateprompt.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGeneratePromptTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGeneratePromptTest::TextAutoGeneratePromptTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGeneratePromptTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGeneratePrompt prompt;
    QVERIFY(prompt.name().isEmpty());
    QVERIFY(prompt.text().isEmpty());
    QVERIFY(prompt.description().isEmpty());
    QVERIFY(prompt.enabled());
    QVERIFY(!prompt.isValid());
    QVERIFY(prompt.identifier().isEmpty());
    QCOMPARE(prompt.category(), TextAutoGenerateText::TextAutoGeneratePrompt::Category::Unknown);
}

void TextAutoGeneratePromptTest::shouldConvertCategoryToString()
{
    QCOMPARE(TextAutoGenerateText::TextAutoGeneratePrompt::convertCategoryToString(TextAutoGenerateText::TextAutoGeneratePrompt::Category::Unknown), QString());
    QCOMPARE(TextAutoGenerateText::TextAutoGeneratePrompt::convertCategoryToString(TextAutoGenerateText::TextAutoGeneratePrompt::Category::Travel),
             u"travel"_s);
    QCOMPARE(TextAutoGenerateText::TextAutoGeneratePrompt::convertCategoryToString(TextAutoGenerateText::TextAutoGeneratePrompt::Category::Code), u"code"_s);
    QCOMPARE(TextAutoGenerateText::TextAutoGeneratePrompt::convertCategoryToString(TextAutoGenerateText::TextAutoGeneratePrompt::Category::Misc), u"misc"_s);
}

void TextAutoGeneratePromptTest::shouldConvertStringToCategory()
{
    QCOMPARE(TextAutoGenerateText::TextAutoGeneratePrompt::convertStringToCategory(u"ddd"_s), TextAutoGenerateText::TextAutoGeneratePrompt::Category::Unknown);
    QCOMPARE(TextAutoGenerateText::TextAutoGeneratePrompt::convertStringToCategory(QString()), TextAutoGenerateText::TextAutoGeneratePrompt::Category::Unknown);
    QCOMPARE(TextAutoGenerateText::TextAutoGeneratePrompt::convertStringToCategory(u"travel"_s),
             TextAutoGenerateText::TextAutoGeneratePrompt::Category::Travel);
    QCOMPARE(TextAutoGenerateText::TextAutoGeneratePrompt::convertStringToCategory(u"code"_s), TextAutoGenerateText::TextAutoGeneratePrompt::Category::Code);
    QCOMPARE(TextAutoGenerateText::TextAutoGeneratePrompt::convertStringToCategory(u"misc"_s), TextAutoGenerateText::TextAutoGeneratePrompt::Category::Misc);
}

#include "moc_textautogenerateprompttest.cpp"
