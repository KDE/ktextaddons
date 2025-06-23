/*
  SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrectiontest.h"
using namespace Qt::Literals::StringLiterals;

#include "../autocorrection.h"
#include "settings/textautocorrectionsettings.h"
#include <QStandardPaths>
#include <QTest>
#include <QTextDocument>
QTEST_MAIN(AutoCorrectionTest)

#ifndef Q_OS_WIN
static void initLocale()
{
    setenv("LC_ALL", "en_US.utf-8", 1);
}

Q_CONSTRUCTOR_FUNCTION(initLocale)
#endif

AutoCorrectionTest::AutoCorrectionTest()
{
    QStandardPaths::setTestModeEnabled(true);
    mConfig = KSharedConfig::openConfig(u"autocorrectiontestrc"_s);
    TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->setSharedConfig(mConfig);
    TextAutoCorrectionCore::TextAutoCorrectionSettings::self()->load();
}

AutoCorrectionTest::~AutoCorrectionTest() = default;

void AutoCorrectionTest::shouldHaveDefaultValue()
{
    TextAutoCorrectionCore::AutoCorrection autocorrection;
    QVERIFY(!autocorrection.autoCorrectionSettings()->isEnabledAutoCorrection());
    QVERIFY(!autocorrection.autoCorrectionSettings()->isUppercaseFirstCharOfSentence());
    QVERIFY(!autocorrection.autoCorrectionSettings()->isFixTwoUppercaseChars());
    QVERIFY(!autocorrection.autoCorrectionSettings()->isSingleSpaces());
    QVERIFY(!autocorrection.autoCorrectionSettings()->isAutoFractions());
    QVERIFY(!autocorrection.autoCorrectionSettings()->isCapitalizeWeekDays());
    QVERIFY(!autocorrection.autoCorrectionSettings()->isReplaceDoubleQuotes());
    QVERIFY(!autocorrection.autoCorrectionSettings()->isReplaceSingleQuotes());
    QVERIFY(!autocorrection.autoCorrectionSettings()->isAdvancedAutocorrect());
    QVERIFY(!autocorrection.autoCorrectionSettings()->isAutoFormatUrl());
    QVERIFY(!autocorrection.autoCorrectionSettings()->isAutoBoldUnderline());
    QVERIFY(!autocorrection.autoCorrectionSettings()->isSuperScript());
    QVERIFY(!autocorrection.autoCorrectionSettings()->isAddNonBreakingSpace());
    QVERIFY(!autocorrection.autoCorrectionSettings()->isReplaceDoubleQuotesByFrenchQuotes());
}

void AutoCorrectionTest::shouldRestoreValue()
{
    TextAutoCorrectionCore::AutoCorrection autocorrection;
    // TODO
}

void AutoCorrectionTest::shouldUpperCaseFirstCharOfSentence()
{
    TextAutoCorrectionCore::AutoCorrection autocorrection;
    auto settings = new TextAutoCorrectionCore::AutoCorrectionSettings;
    settings->setEnabledAutoCorrection(true);
    settings->setUppercaseFirstCharOfSentence(true);
    autocorrection.setAutoCorrectionSettings(settings);

    // Uppercase here.
    QTextDocument doc;
    QString text = u"foo"_s;
    doc.setPlainText(text);
    int position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), u"Foo"_s);

    // IT's not first char -> not uppercase
    text = u" foo"_s;
    doc.setPlainText(text);
    position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), text);

    // It's already uppercase
    text = u"Foo"_s;
    doc.setPlainText(text);
    position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), text);

    // Word is after a ". "
    text = u"Foo. foo"_s;
    doc.setPlainText(text);
    position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), u"Foo. Foo"_s);
    QCOMPARE(position, text.length());
}

void AutoCorrectionTest::shouldFixTwoUpperCaseChars()
{
    TextAutoCorrectionCore::AutoCorrection autocorrection;
    auto settings = new TextAutoCorrectionCore::AutoCorrectionSettings;
    settings->setEnabledAutoCorrection(true);
    settings->setFixTwoUppercaseChars(true);
    autocorrection.setAutoCorrectionSettings(settings);

    // Remove two uppercases
    QTextDocument doc;
    QString text = u"FOo"_s;
    doc.setPlainText(text);
    int position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), u"Foo"_s);

    // There is not two uppercase
    text = u"foo"_s;
    doc.setPlainText(text);
    position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), text);

    text = u"Foo"_s;
    doc.setPlainText(text);
    position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), text);

    // There is a uppercase word
    text = u"FOO"_s;
    doc.setPlainText(text);
    position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), text);

    // Exclude 2 upper letter
    text = u"ABc"_s;
    doc.setPlainText(text);
    position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), u"Abc"_s);

    QSet<QString> exception;
    exception.insert(u"ABc"_s);
    settings->setTwoUpperLetterExceptions(exception);
    autocorrection.setAutoCorrectionSettings(settings);
    text = u"ABc"_s;
    doc.setPlainText(text);
    position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), text);
}

void AutoCorrectionTest::shouldReplaceSingleQuote()
{
    TextAutoCorrectionCore::AutoCorrection autocorrection;
    auto settings = new TextAutoCorrectionCore::AutoCorrectionSettings;
    settings->setEnabledAutoCorrection(true);
    settings->setReplaceSingleQuotes(true);
    autocorrection.setAutoCorrectionSettings(settings);

    TextAutoCorrectionCore::AutoCorrectionUtils::TypographicQuotes simpleQuote;
    simpleQuote.begin = u'A';
    simpleQuote.end = u'B';

    settings->setTypographicSingleQuotes(simpleQuote);
    autocorrection.setAutoCorrectionSettings(settings);

    QTextDocument doc;
    QString text = u"sss"_s;
    doc.setPlainText(u"'"_s + text);
    int position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), QString(simpleQuote.begin + text));

    text = u"sss"_s;
    doc.setPlainText(text + u"'"_s);
    position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), QString(text + simpleQuote.end));

    text = u"sss"_s;
    doc.setPlainText(u"'"_s + text + u"'"_s);
    position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), QString(simpleQuote.begin + text + simpleQuote.end));
}

void AutoCorrectionTest::shouldReplaceDoubleQuote()
{
    TextAutoCorrectionCore::AutoCorrection autocorrection;
    auto settings = new TextAutoCorrectionCore::AutoCorrectionSettings;
    settings->setEnabledAutoCorrection(true);
    settings->setReplaceDoubleQuotes(true);
    TextAutoCorrectionCore::AutoCorrectionUtils::TypographicQuotes doubleQuote;
    doubleQuote.begin = u'A';
    doubleQuote.end = u'B';

    settings->setTypographicDoubleQuotes(doubleQuote);
    autocorrection.setAutoCorrectionSettings(settings);

    QTextDocument doc;
    QString text = u"sss"_s;

    doc.setPlainText(u'"' + text);
    int position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), QString(doubleQuote.begin + text));

    text = u"sss"_s;
    doc.setPlainText(text + u"\""_s);
    position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), QString(text + doubleQuote.end));

    text = u"sss"_s;
    doc.setPlainText(u"\""_s + text + u"\""_s);
    position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), QString(doubleQuote.begin + text + doubleQuote.end));
}

void AutoCorrectionTest::shouldNotReplaceUppercaseLetter()
{
    TextAutoCorrectionCore::AutoCorrection autocorrection;
    auto settings = new TextAutoCorrectionCore::AutoCorrectionSettings;
    settings->setEnabledAutoCorrection(true);
    settings->setFixTwoUppercaseChars(true);
    autocorrection.setAutoCorrectionSettings(settings);
    QSet<QString> exceptions;
    exceptions.insert(u"ABc"_s);
    settings->setTwoUpperLetterExceptions(exceptions);
    autocorrection.setAutoCorrectionSettings(settings);

    QTextDocument doc;
    QString text = u"foo ABc"_s;
    doc.setPlainText(text);
    int position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), text);
}

void AutoCorrectionTest::shouldReplaceToTextFormat()
{
    TextAutoCorrectionCore::AutoCorrection autocorrection;
    auto settings = new TextAutoCorrectionCore::AutoCorrectionSettings;
    settings->setEnabledAutoCorrection(true);
    settings->setAutoBoldUnderline(true);
    autocorrection.setAutoCorrectionSettings(settings);

    QTextDocument doc;
    // We don't use html => don't change it.
    QString text = u"*foo*"_s;
    doc.setHtml(text);
    int position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), text);

    QString result = u"foo"_s;
    doc.setHtml(text);
    position = text.length();
    autocorrection.autocorrect(true, doc, position);
    QCOMPARE(doc.toPlainText(), result);

    text = u"*foo*"_s;
    doc.setHtml(text);
    position = text.length();
    autocorrection.autocorrect(true, doc, position);
    QCOMPARE(doc.toPlainText(), result);
    QTextCursor cursor(&doc);
    cursor.setPosition(2);
    QTextCharFormat charFormat = cursor.charFormat();
    QCOMPARE(charFormat.font().underline(), false);
    QCOMPARE(charFormat.font().bold(), true);
    QCOMPARE(charFormat.font().strikeOut(), false);

    text = u"_foo_"_s;
    doc.setHtml(text);
    position = text.length();
    autocorrection.autocorrect(true, doc, position);
    QCOMPARE(doc.toPlainText(), result);
    cursor = QTextCursor(&doc);
    cursor.setPosition(2);
    charFormat = cursor.charFormat();
    QCOMPARE(charFormat.font().underline(), true);
    QCOMPARE(charFormat.font().bold(), false);
    QCOMPARE(charFormat.font().strikeOut(), false);

    text = u"-foo-"_s;
    doc.setHtml(text);
    position = text.length();
    autocorrection.autocorrect(true, doc, position);
    QCOMPARE(doc.toPlainText(), result);
    cursor = QTextCursor(&doc);
    cursor.setPosition(2);
    charFormat = cursor.charFormat();
    QCOMPARE(charFormat.font().underline(), false);
    QCOMPARE(charFormat.font().bold(), false);
    QCOMPARE(charFormat.font().strikeOut(), true);

    // Don't convert it.
    text = u"-foo1"_s;
    doc.setHtml(text);
    position = text.length();
    autocorrection.autocorrect(true, doc, position);
    QCOMPARE(doc.toPlainText(), text);

    text = u"*foo* blabla"_s;
    position = 5;
    doc.setHtml(text);
    autocorrection.autocorrect(true, doc, position);
    result = u"foo blabla"_s;
    QCOMPARE(doc.toPlainText(), result);
    QCOMPARE(position, 3);

    // TODO QCOMPARE(doc.toHtml(), text);
}

void AutoCorrectionTest::shouldReplaceAutoFraction()
{
    TextAutoCorrectionCore::AutoCorrection autocorrection;
    auto settings = new TextAutoCorrectionCore::AutoCorrectionSettings;
    settings->setEnabledAutoCorrection(true);
    settings->setAutoFractions(true);
    autocorrection.setAutoCorrectionSettings(settings);

    QTextDocument doc;
    QString text = u"1/2"_s;
    doc.setPlainText(text);
    int position = text.length();
    autocorrection.autocorrect(false, doc, position);

    QCOMPARE(doc.toPlainText(), u"½"_s);

    QString suffix = u" after"_s;
    text = u"1/2"_s;
    position = 3;
    text += suffix;
    doc.setPlainText(text);
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), QString(u"½"_s + suffix));
    QCOMPARE(position, 1);
}

void AutoCorrectionTest::shouldNotAddSpaceWhenWeAlreadyHaveASpace()
{
    TextAutoCorrectionCore::AutoCorrection autocorrection;
    auto settings = new TextAutoCorrectionCore::AutoCorrectionSettings;
    settings->setEnabledAutoCorrection(true);
    settings->setSingleSpaces(true);
    autocorrection.setAutoCorrectionSettings(settings);
    QTextDocument doc;
    // We already a space => don't allow to add more
    QString text = u"FOO "_s;
    doc.setPlainText(text);
    int position = text.length();
    bool result = autocorrection.autocorrect(false, doc, position);
    QCOMPARE(result, false);

    // We can add a space
    text = u"FOO"_s;
    doc.setPlainText(text);
    position = text.length();
    result = autocorrection.autocorrect(false, doc, position);
    QCOMPARE(result, true);

    // We have a space => don't add it.
    text = u"FOO "_s;
    position = text.length();
    QString fullText = text + u"FOO"_s;
    doc.setPlainText(fullText);
    result = autocorrection.autocorrect(false, doc, position);
    QCOMPARE(result, false);
}

void AutoCorrectionTest::shouldAutocorrectWord()
{
    TextAutoCorrectionCore::AutoCorrection autocorrection;
    auto settings = new TextAutoCorrectionCore::AutoCorrectionSettings;
    settings->setEnabledAutoCorrection(true);
    settings->setAdvancedAutocorrect(true);
    autocorrection.setAutoCorrectionSettings(settings);

    QTextDocument doc;
    // No changes
    QString text = u"FOOAA"_s;
    doc.setPlainText(text);
    int position = text.length();
    int oldPosition = position;
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), text);
    QCOMPARE(position, oldPosition);

    // Convert word
    QHash<QString, QString> entries;
    const QString convertWord = u"BLABLA"_s;
    entries.insert(text, convertWord);
    settings->setAutocorrectEntries(entries);
    autocorrection.setAutoCorrectionSettings(settings);
    text = u"FOOAA"_s;
    doc.setPlainText(text);
    position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), convertWord);
    QCOMPARE(position, convertWord.length());

    QString suffix = u" TOTO"_s;
    text = u"FOOAA"_s;
    position = text.length();
    text += suffix;
    doc.setPlainText(text);
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), QString(convertWord + suffix));
    // FIXME ? QCOMPARE(position, convertWord.length());
}

void AutoCorrectionTest::shouldNotUpperCaseFirstCharOfSentence()
{
    TextAutoCorrectionCore::AutoCorrection autocorrection;
    auto settings = new TextAutoCorrectionCore::AutoCorrectionSettings;
    settings->setEnabledAutoCorrection(true);
    settings->setUppercaseFirstCharOfSentence(true);
    autocorrection.setAutoCorrectionSettings(settings);
    QSet<QString> lst;
    lst.insert(u"Foo."_s);
    settings->setUpperCaseExceptions(lst);
    autocorrection.setAutoCorrectionSettings(settings);

    // Uppercase here.
    QTextDocument doc;
    QString text = u"foo. blabla Foo. tt"_s;
    doc.setPlainText(text);
    int position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), text);

    settings->setUpperCaseExceptions(QSet<QString>());
    autocorrection.setAutoCorrectionSettings(settings);

    doc.setPlainText(text);
    position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QString result = u"foo. blabla Foo. Tt"_s;
    QCOMPARE(doc.toPlainText(), result);
}

using mapAutoCorrect = QHash<QString, QString>;
Q_DECLARE_METATYPE(mapAutoCorrect)

void AutoCorrectionTest::shouldAutocorrectMultiWord_data()
{
    QTest::addColumn<QString>("originalString");
    QTest::addColumn<QString>("convertedString");
    QTest::addColumn<mapAutoCorrect>("convertStringHash");

    mapAutoCorrect map;
    map.insert(u"boo"_s, u"bla"_s);
    QTest::newRow("simpleReplace") << u"boo"_s << u"bla"_s << map;

    map.clear();
    map.insert(u"a boo"_s, u"b bla"_s);
    QTest::newRow("multiword") << u"a boo"_s << u"b bla"_s << map;

    map.clear();
    map.insert(u"a boo"_s, u"b bla"_s);
    map.insert(u"a booeeeeeeeeeeeeeeeeeee"_s, u"b blaeee"_s);
    QTest::newRow("multiword-2") << u"toto. a boo"_s << u"toto. b bla"_s << map;

    map.clear();
    QTest::newRow("multiword-2 without replace") << u"toto. a boo"_s << u"toto. a boo"_s << map;

    map.clear();
    map.insert(u"a boo"_s, u"b bla"_s);
    QTest::newRow("multiword-2 with uppercase") << u"toto. A boo"_s << u"toto. B bla"_s << map;

    map.clear();
    map.insert(u"a boo1111111111"_s, u"b bla"_s);
    QTest::newRow("multiword-3") << u"a boo"_s << u"a boo"_s << map;

    map.clear();
    map.insert(u"boo"_s, u"Bla"_s);
    QTest::newRow("withuppercase") << u"Boo"_s << u"Bla"_s << map;

    map.clear();
    map.insert(u"boo"_s, u"bla"_s);
    QTest::newRow("withuppercase-2") << u"Boo"_s << u"Bla"_s << map;

    map.clear();
    map.insert(u"boo"_s, u"Bla"_s);
    QTest::newRow("withuppercase-3") << u"Boo"_s << u"Bla"_s << map;

    map.clear();
    map.insert(u"boo"_s, u"Bla"_s);
    QTest::newRow("withuppercase-4") << u"boo"_s << u"bla"_s << map;

    map.clear();
    map.insert(u"booooo"_s, u"bla"_s);
    QTest::newRow("nofindtext") << u"boo"_s << u"boo"_s << map;

    map.clear();
    map.insert(u"boosss"_s, u"Blasss"_s);
    map.insert(u"boo"_s, u"bla"_s);
    QTest::newRow("withponct") << u"boo!"_s << u"bla!"_s << map;

    map.clear();
    map.insert(u"boosss"_s, u"Blasss"_s);
    map.insert(u"boo"_s, u"bla"_s);
    QTest::newRow("withponct-2") << u"lolo. boo!"_s << u"lolo. bla!"_s << map;

    map.clear();
    map.insert(u"boo"_s, u"bla"_s);
    QTest::newRow("dontreplaceinpieceofword") << u"voitureboo"_s << u"voitureboo"_s << map;

    map.clear();
    map.insert(u"boo"_s, u"bla"_s);
    QTest::newRow("dontreplaceall") << u"Boo boo boo"_s << u"Boo boo bla"_s << map;

    map.clear();
    map.insert(u"boo"_s, u"bla"_s);
    map.insert(u"boo boo"_s, u"bli"_s);
    QTest::newRow("replace-1") << u"Boo boo boo"_s << u"Boo bli"_s << map;

    map.clear();
    map.insert(u"boo boo"_s, u"bli"_s);
    map.insert(u"boo"_s, u"bla"_s);
    QTest::newRow("replace-1-order") << u"Boo boo boo"_s << u"Boo bli"_s << map;

    map.clear();
    map.insert(u"au delà"_s, u"au-delà"_s);
    map.insert(u"boo boo"_s, u"bli"_s);
    QTest::newRow("replace-2") << u"voilà au delà"_s << u"voilà au-delà"_s << map;

    map.clear();
    map.insert(u"au delà"_s, u"au-delà"_s);
    map.insert(u"avant JC"_s, u"avant J.-C."_s);
    QTest::newRow("replace-3") << u"il est né avant JC"_s << u"il est né avant J.-C."_s << map;
}

void AutoCorrectionTest::shouldAutocorrectMultiWord()
{
    QFETCH(QString, originalString);
    QFETCH(QString, convertedString);
    QFETCH(mapAutoCorrect, convertStringHash);

    TextAutoCorrectionCore::AutoCorrection autocorrection;
    auto settings = new TextAutoCorrectionCore::AutoCorrectionSettings;
    settings->setEnabledAutoCorrection(true);
    settings->setAdvancedAutocorrect(true);
    settings->setAutocorrectEntries(convertStringHash);
    autocorrection.setAutoCorrectionSettings(settings);

    QTextDocument doc;
    doc.setPlainText(originalString);
    int position = originalString.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), convertedString);
}

void AutoCorrectionTest::shouldAddNonBreakingSpace_data()
{
    QTest::addColumn<QString>("originalString");
    QTest::addColumn<QString>("convertedString");
    QTest::addColumn<QString>("language");
    QTest::addColumn<bool>("enableAddNonBreakingSpace");
    QTest::newRow("convert1") << u"boo !"_s << u"boob!"_s << QStringLiteral("fr") << true;
    QTest::newRow("disable") << u"boo !"_s << u"boo !"_s << QStringLiteral("fr") << false;
    QTest::newRow("nonchanges") << u"boo"_s << u"boo"_s << QStringLiteral("fr") << true;
    QTest::newRow("convert2") << u"boo ;"_s << u"boob;"_s << QStringLiteral("fr") << true;
    QTest::newRow("convert3") << u"boo ?"_s << u"boob?"_s << QStringLiteral("fr") << true;
    QTest::newRow("convert4") << u"boo :"_s << u"boob:"_s << QStringLiteral("fr") << true;
    QTest::newRow("nonfrenchlanguage") << u"boo :"_s << u"boo :"_s << QStringLiteral("ge") << true;
    QTest::newRow("onecharacter") << u":"_s << u":"_s << QStringLiteral("fr") << true;
    QTest::newRow("onecharacter2") << u" "_s << u" "_s << QStringLiteral("fr") << true;
    QTest::newRow("percentage") << u"50 %"_s << u"50b%"_s << QStringLiteral("fr") << true;
    QTest::newRow("degrees") << u"50 °C"_s << u"50b°C"_s << QStringLiteral("fr") << true;
    QTest::newRow("simplespace") << u" "_s << u" "_s << QStringLiteral("fr") << true;
}

void AutoCorrectionTest::shouldAddNonBreakingSpace()
{
    QFETCH(QString, originalString);
    QFETCH(QString, convertedString);
    QFETCH(QString, language);
    QFETCH(bool, enableAddNonBreakingSpace);

    TextAutoCorrectionCore::AutoCorrection autocorrection;
    auto settings = new TextAutoCorrectionCore::AutoCorrectionSettings;
    settings->setEnabledAutoCorrection(true);
    settings->setAddNonBreakingSpace(enableAddNonBreakingSpace);

    settings->setLanguage(language);
    settings->setNonBreakingSpace(QChar(u'b'));
    autocorrection.setAutoCorrectionSettings(settings);

    QTextDocument doc;
    doc.setPlainText(originalString);
    int position = originalString.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), convertedString);
}

void AutoCorrectionTest::shouldReplaceWithMultiOption_data()
{
    QTest::addColumn<QString>("originalString");
    QTest::addColumn<QString>("convertedString");
    QTest::addColumn<mapAutoCorrect>("convertStringHash");

    QTest::addColumn<bool>("enable");
    QTest::addColumn<bool>("uppercaseFirstCharOfSentence");
    QTest::addColumn<bool>("advancedAutocorrect");
    QTest::addColumn<bool>("fixtwouppercase");
    QTest::addColumn<int>("position");
    mapAutoCorrect map;
    map.insert(u"boo"_s, u"bla"_s);
    map.insert(u":j2:"_s, u"TV"_s);
    map.insert(u"i"_s, u"I"_s);
    map.insert(u"Noel"_s, u"noal"_s);
    // create a big word otherwise we can't reproduce bug
    map.insert(u"anticonstitutionnellement"_s, u"2"_s);

    QTest::newRow("disable") << u"Boo boo boo"_s << u"Boo boo boo"_s << map << false << false << false << false << -1;
    QTest::newRow("enablebutdisablealloptions") << u"Boo boo boo"_s << u"Boo boo boo"_s << map << true << false << false << false << -1;
    QTest::newRow("enableandenableuppercase") << u"Boo boo boo"_s << u"Boo boo boo"_s << map << true << true << false << false << -1;
    QTest::newRow("enableandenableuppercaseandadvanced") << u"Boo boo boo"_s << u"Boo boo bla"_s << map << true << true << true << false << -1;

    QTest::newRow("enableandenableuppercaseandadvanced-2") << u"Boo boo. boo"_s << u"Boo boo. Bla"_s << map << true << true << true << false << -1;
    QTest::newRow("enableandenableuppercaseandadvanced-3") << u"blablobli"_s << u"Blablobli"_s << map << true << true << true << false << -1;
    QTest::newRow("enableandenableuppercaseandadvanced-4") << u"blablobli. foo"_s << u"blablobli. Foo"_s << map << true << true << true << false << -1;

    QTest::newRow("enableandenablefixtowuppercase") << u"Boo boo. BOo"_s << u"Boo boo. Boo"_s << map << true << true << false << true << -1;
    QTest::newRow("enableandenablefixtowuppercase-2") << u"Boo BOo"_s << u"Boo Boo"_s << map << true << true << false << true << -1;

    QTest::newRow(":j2:") << u":j2:"_s << u"TV"_s << map << true << false << true << false << -1;
    QTest::newRow(":j2: bla") << u":j2: bla"_s << u":j2: bla"_s << map << true << false << true << false << -1;
    QTest::newRow(":j2: bla 1") << u":j2: bla"_s << u"TV bla"_s << map << true << false << true << false << 4;
    QTest::newRow(":j2: bla 2") << u":j2: :j2:"_s << u":j2: TV"_s << map << true << false << true << false << -1;
    QTest::newRow("La mais il n est pas ici ") << u"La mais il n est pas ici "_s << u"La mais il n est pas ici "_s << map << true << false << true << false
                                               << 25;
    QTest::newRow("a noel") << u"a noel"_s << u"a noal"_s << map << true << false << true << false << 6;
    // TODO add more
}

void AutoCorrectionTest::shouldReplaceWithMultiOption()
{
    QFETCH(QString, originalString);
    QFETCH(QString, convertedString);
    QFETCH(mapAutoCorrect, convertStringHash);
    QFETCH(bool, enable);
    QFETCH(bool, uppercaseFirstCharOfSentence);
    QFETCH(bool, advancedAutocorrect);
    QFETCH(bool, fixtwouppercase);
    QFETCH(int, position);

    TextAutoCorrectionCore::AutoCorrection autocorrection;
    auto settings = new TextAutoCorrectionCore::AutoCorrectionSettings;
    settings->setEnabledAutoCorrection(enable);
    settings->setAdvancedAutocorrect(advancedAutocorrect);
    settings->setAutocorrectEntries(convertStringHash);
    settings->setUppercaseFirstCharOfSentence(uppercaseFirstCharOfSentence);
    settings->setFixTwoUppercaseChars(fixtwouppercase);
    autocorrection.setAutoCorrectionSettings(settings);

    QTextDocument doc;
    doc.setPlainText(originalString);
    position = (position == -1) ? originalString.length() : position;
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), convertedString);
}

void AutoCorrectionTest::shouldAddNonBreakingSpaceBeforeAfterQuote()
{
    TextAutoCorrectionCore::AutoCorrection autocorrection;
    auto settings = new TextAutoCorrectionCore::AutoCorrectionSettings;
    settings->setEnabledAutoCorrection(true);
    settings->setReplaceDoubleQuotes(true);
    settings->setReplaceSingleQuotes(true);
    settings->setLanguage(u"fr"_s);
    settings->setAddNonBreakingSpace(true);
    // TODO fix me verify why it doesn't use no breaking space
    const QChar nbsp = QChar(/*QChar::Nbsp*/ u'b');
    settings->setNonBreakingSpace(nbsp);
    autocorrection.setAutoCorrectionSettings(settings);

    TextAutoCorrectionCore::AutoCorrectionUtils::TypographicQuotes doubleQuote;
    doubleQuote.begin = u'A';
    doubleQuote.end = u'B';
    settings->setTypographicDoubleQuotes(doubleQuote);

    TextAutoCorrectionCore::AutoCorrectionUtils::TypographicQuotes simpleQuote;
    simpleQuote.begin = u'A';
    simpleQuote.end = u'B';

    settings->setTypographicSingleQuotes(simpleQuote);
    autocorrection.setAutoCorrectionSettings(settings);

    QTextDocument doc;
    QString text = u"sss"_s;

    doc.setPlainText(u'"' + text);
    int position = text.length();
    autocorrection.autocorrect(false, doc, position);

    QCOMPARE(doc.toPlainText(), QString(doubleQuote.begin + nbsp + text));

    text = u"sss"_s;
    doc.setPlainText(text + u"\""_s);
    position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), QString(text + nbsp + doubleQuote.end));

    // Simple quote
    text = u"sss"_s;
    doc.setPlainText(text + u"\'"_s);
    position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), QString(text + nbsp + simpleQuote.end));

    text = u"sss"_s;
    doc.setPlainText(u"\""_s + text + u"\""_s);
    position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), QString(doubleQuote.begin + nbsp + text + nbsp + doubleQuote.end));

    // Simple quote
    text = u"sss"_s;
    doc.setPlainText(u"\'"_s + text + u"\'"_s);
    position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), QString(simpleQuote.begin + nbsp + text + nbsp + simpleQuote.end));

    text = u'(';
    doc.setPlainText(u"\""_s + text + u"\""_s);
    position = text.length();
    autocorrection.autocorrect(false, doc, position);
    QCOMPARE(doc.toPlainText(), QString(doubleQuote.begin + nbsp + text + nbsp + doubleQuote.end));
}

void AutoCorrectionTest::shouldAutoFormatURLs()
{
    TextAutoCorrectionCore::AutoCorrection autocorrection;
    auto settings = new TextAutoCorrectionCore::AutoCorrectionSettings;
    settings->setAutoFormatUrl(true);
    autocorrection.setAutoCorrectionSettings(settings);
    // autocorrection.autocorrect(true, doc, position);

    //    QTextCursor cursor(&doc);
    //    cursor.setPosition(2);
    //    QTextCharFormat charFormat = cursor.charFormat();
    //    QCOMPARE(charFormat.font().underline(), false);
    //    QCOMPARE(charFormat.font().bold(), true);
    //    QCOMPARE(charFormat.font().strikeOut(), false);
}

#include "moc_autocorrectiontest.cpp"
