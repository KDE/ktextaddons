/*
  SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrectiontextedittest.h"
using namespace Qt::Literals::StringLiterals;

#include "autocorrection.h"
#include "autocorrectionsettings.h"
#include <QStandardPaths>
#include <QTest>
#include <TextAutoCorrection/AutoCorrectionTextEdit>
#include <qtestkeyboard.h>

AutoCorrectionTextEditTest::AutoCorrectionTextEditTest()
{
    QStandardPaths::setTestModeEnabled(true);
}

void AutoCorrectionTextEditTest::shouldNotAutocorrectWhenDisabled()
{
    TextAutoCorrection::AutoCorrectionTextEdit richtext(nullptr);
    QHash<QString, QString> entries;
    const QString originalWord = u"FOOFOO"_s;
    const QString replaceWord = u"BLABLA"_s;
    entries.insert(originalWord, replaceWord);
    auto settings = new TextAutoCorrection::AutoCorrectionSettings;
    settings->setAutocorrectEntries(entries);
    richtext.autocorrection()->setAutoCorrectionSettings(settings);
    richtext.show();
    QVERIFY(QTest::qWaitForWindowExposed(&richtext));
    QTest::keyClicks(&richtext, originalWord);
    QTest::keyClick(&richtext, ' ');
    QCOMPARE(richtext.toPlainText(), QString(originalWord + u' '));
}

void AutoCorrectionTextEditTest::shouldReplaceWordWhenExactText()
{
    TextAutoCorrection::AutoCorrectionTextEdit richtext(nullptr);
    const QString originalWord = u"FOOFOO"_s;
    const QString replaceWord = u"BLABLA"_s;
    QHash<QString, QString> entries;
    entries.insert(originalWord, replaceWord);
    auto settings = new TextAutoCorrection::AutoCorrectionSettings;
    settings->setAutocorrectEntries(entries);
    settings->setEnabledAutoCorrection(true);
    settings->setAdvancedAutocorrect(true);
    richtext.autocorrection()->setAutoCorrectionSettings(settings);
    richtext.show();
    QVERIFY(QTest::qWaitForWindowExposed(&richtext));
    QTest::keyClicks(&richtext, originalWord);
    QTest::keyClick(&richtext, ' ');
    QCOMPARE(richtext.toPlainText(), QString(replaceWord + u' '));
}

void AutoCorrectionTextEditTest::shouldNotReplaceWordWhenInexactText()
{
    TextAutoCorrection::AutoCorrectionTextEdit richtext(nullptr);
    const QString originalWord = u"FOOFOO"_s;
    const QString replaceWord = u"BLABLA"_s;
    QHash<QString, QString> entries;
    entries.insert(originalWord, replaceWord);
    auto settings = new TextAutoCorrection::AutoCorrectionSettings;
    settings->setAutocorrectEntries(entries);
    settings->setEnabledAutoCorrection(true);
    settings->setAdvancedAutocorrect(true);
    richtext.autocorrection()->setAutoCorrectionSettings(settings);

    richtext.show();
    const QString nonExactText = u"BLIBLI"_s;
    QVERIFY(QTest::qWaitForWindowExposed(&richtext));
    QTest::keyClicks(&richtext, nonExactText);
    QTest::keyClick(&richtext, ' ');
    QCOMPARE(richtext.toPlainText(), QString(nonExactText + u' '));
}

void AutoCorrectionTextEditTest::shouldReplaceWhenPressEnter()
{
    TextAutoCorrection::AutoCorrectionTextEdit richtext(nullptr);
    const QString originalWord = u"FOOFOO"_s;
    const QString replaceWord = u"BLABLA"_s;
    QHash<QString, QString> entries;
    entries.insert(originalWord, replaceWord);

    auto settings = new TextAutoCorrection::AutoCorrectionSettings;
    settings->setAutocorrectEntries(entries);
    settings->setEnabledAutoCorrection(true);
    settings->setAdvancedAutocorrect(true);
    richtext.autocorrection()->setAutoCorrectionSettings(settings);

    richtext.show();
    QVERIFY(QTest::qWaitForWindowExposed(&richtext));
    QTest::keyClicks(&richtext, originalWord);
    QTest::keyPress(&richtext, Qt::Key_Enter);
    QCOMPARE(richtext.toPlainText(), QString(replaceWord + u'\n'));
}

void AutoCorrectionTextEditTest::shouldReplaceWhenPressReturn()
{
    TextAutoCorrection::AutoCorrectionTextEdit richtext(nullptr);
    const QString originalWord = u"FOOFOO"_s;
    const QString replaceWord = u"BLABLA"_s;
    QHash<QString, QString> entries;
    entries.insert(originalWord, replaceWord);
    auto settings = new TextAutoCorrection::AutoCorrectionSettings;
    settings->setAutocorrectEntries(entries);
    settings->setEnabledAutoCorrection(true);
    settings->setAdvancedAutocorrect(true);
    richtext.autocorrection()->setAutoCorrectionSettings(settings);
    richtext.show();
    QVERIFY(QTest::qWaitForWindowExposed(&richtext));
    QTest::keyClicks(&richtext, originalWord);
    QTest::keyPress(&richtext, Qt::Key_Return);
    QCOMPARE(richtext.toPlainText(), QString(replaceWord + u'\n'));
}

QTEST_MAIN(AutoCorrectionTextEditTest)

#include "moc_autocorrectiontextedittest.cpp"
