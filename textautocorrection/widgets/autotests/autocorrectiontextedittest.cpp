/*
  SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrectiontextedittest.h"
using namespace Qt::Literals::StringLiterals;

#include <QPlainTextEdit>
#include <QStandardPaths>
#include <QTest>
#include <QTextEdit>
#include <TextAutoCorrectionCore/AutoCorrection>
#include <TextAutoCorrectionCore/AutoCorrectionSettings>
#include <TextAutoCorrectionWidgets/AutoCorrector>

using namespace TextAutoCorrectionWidgets;

static TextAutoCorrectionCore::AutoCorrectionSettings *createSettings(const QString &originalWord, const QString &replaceWord, bool enabled)
{
    QHash<QString, QString> entries;
    entries.insert(originalWord, replaceWord);
    auto settings = new TextAutoCorrectionCore::AutoCorrectionSettings;
    settings->setAutocorrectEntries(entries);
    settings->setEnabledAutoCorrection(enabled);
    settings->setAdvancedAutocorrect(enabled);
    return settings;
}

AutoCorrectionTextEditTest::AutoCorrectionTextEditTest()
{
    QStandardPaths::setTestModeEnabled(true);
}

void AutoCorrectionTextEditTest::shouldNotAutocorrectWhenDisabled()
{
    QTextEdit richtext;
    const QString originalWord = u"FOOFOO"_s;
    const QString replaceWord = u"BLABLA"_s;
    auto corrector = new AutoCorrector(&richtext);
    corrector->autocorrection()->setAutoCorrectionSettings(createSettings(originalWord, replaceWord, false));
    richtext.show();
    QVERIFY(QTest::qWaitForWindowExposed(&richtext));
    QTest::keyClicks(&richtext, originalWord);
    QTest::keyClick(&richtext, ' ');
    QCOMPARE(richtext.toPlainText(), QString(originalWord + u' '));
}

void AutoCorrectionTextEditTest::shouldReplaceWordWhenExactText()
{
    QTextEdit richtext;
    const QString originalWord = u"FOOFOO"_s;
    const QString replaceWord = u"BLABLA"_s;
    auto corrector = new AutoCorrector(&richtext);
    corrector->autocorrection()->setAutoCorrectionSettings(createSettings(originalWord, replaceWord, true));
    richtext.show();
    QVERIFY(QTest::qWaitForWindowExposed(&richtext));
    QTest::keyClicks(&richtext, originalWord);
    QTest::keyClick(&richtext, ' ');
    QCOMPARE(richtext.toPlainText(), QString(replaceWord + u' '));
}

void AutoCorrectionTextEditTest::shouldNotReplaceWordWhenInexactText()
{
    QTextEdit richtext;
    const QString originalWord = u"FOOFOO"_s;
    const QString replaceWord = u"BLABLA"_s;
    auto corrector = new AutoCorrector(&richtext);
    corrector->autocorrection()->setAutoCorrectionSettings(createSettings(originalWord, replaceWord, true));
    richtext.show();
    const QString nonExactText = u"BLIBLI"_s;
    QVERIFY(QTest::qWaitForWindowExposed(&richtext));
    QTest::keyClicks(&richtext, nonExactText);
    QTest::keyClick(&richtext, ' ');
    QCOMPARE(richtext.toPlainText(), QString(nonExactText + u' '));
}

void AutoCorrectionTextEditTest::shouldReplaceWhenPressEnter()
{
    QTextEdit richtext;
    const QString originalWord = u"FOOFOO"_s;
    const QString replaceWord = u"BLABLA"_s;
    auto corrector = new AutoCorrector(&richtext);
    corrector->autocorrection()->setAutoCorrectionSettings(createSettings(originalWord, replaceWord, true));
    richtext.show();
    QVERIFY(QTest::qWaitForWindowExposed(&richtext));
    QTest::keyClicks(&richtext, originalWord);
    QTest::keyPress(&richtext, Qt::Key_Enter);
    QCOMPARE(richtext.toPlainText(), QString(replaceWord + u'\n'));
}

void AutoCorrectionTextEditTest::shouldReplaceWhenPressReturn()
{
    QTextEdit richtext;
    const QString originalWord = u"FOOFOO"_s;
    const QString replaceWord = u"BLABLA"_s;
    auto corrector = new AutoCorrector(&richtext);
    corrector->autocorrection()->setAutoCorrectionSettings(createSettings(originalWord, replaceWord, true));
    richtext.show();
    QVERIFY(QTest::qWaitForWindowExposed(&richtext));
    QTest::keyClicks(&richtext, originalWord);
    QTest::keyPress(&richtext, Qt::Key_Return);
    QCOMPARE(richtext.toPlainText(), QString(replaceWord + u'\n'));
}

void AutoCorrectionTextEditTest::shouldAutocorrectPlainTextEdit()
{
    QPlainTextEdit plaintext;
    const QString originalWord = u"FOOFOO"_s;
    const QString replaceWord = u"BLABLA"_s;
    auto corrector = new AutoCorrector(&plaintext);
    corrector->autocorrection()->setAutoCorrectionSettings(createSettings(originalWord, replaceWord, true));
    plaintext.show();
    QVERIFY(QTest::qWaitForWindowExposed(&plaintext));
    QTest::keyClicks(&plaintext, originalWord);
    QTest::keyClick(&plaintext, ' ');
    QCOMPARE(plaintext.toPlainText(), QString(replaceWord + u' '));
}

void AutoCorrectionTextEditTest::shouldNotModifyReadOnlyEditor()
{
    QTextEdit richtext;
    const QString originalWord = u"FOOFOO"_s;
    const QString replaceWord = u"BLABLA"_s;
    richtext.setPlainText(originalWord);
    richtext.setReadOnly(true);
    auto corrector = new AutoCorrector(&richtext);
    corrector->autocorrection()->setAutoCorrectionSettings(createSettings(originalWord, replaceWord, true));
    richtext.show();
    QVERIFY(QTest::qWaitForWindowExposed(&richtext));
    QTest::keyClick(&richtext, ' ');
    QCOMPARE(richtext.toPlainText(), originalWord);
}

void AutoCorrectionTextEditTest::shouldNotEatKeyWhenTextIsSelected()
{
    const QString text = u"hello world"_s;
    // A key press over a selection must be handled by the editor itself, exactly as if no AutoCorrector was installed.
    const auto typeSpaceOverSelection = [&text](bool installAutoCorrector) {
        QTextEdit richtext;
        richtext.setPlainText(text);
        if (installAutoCorrector) {
            auto corrector = new AutoCorrector(&richtext);
            corrector->autocorrection()->setAutoCorrectionSettings(createSettings(u"FOOFOO"_s, u"BLABLA"_s, true));
        }
        richtext.show();
        [[maybe_unused]] const bool exposed = QTest::qWaitForWindowExposed(&richtext);
        QTextCursor cursor = richtext.textCursor();
        cursor.setPosition(0);
        cursor.setPosition(5, QTextCursor::KeepAnchor); // select "hello"
        richtext.setTextCursor(cursor);
        QTest::keyClick(&richtext, ' ');
        return richtext.toPlainText();
    };

    const QString withoutAutoCorrector = typeSpaceOverSelection(false);
    QVERIFY(withoutAutoCorrector != text); // the selection was replaced
    const QString withAutoCorrector = typeSpaceOverSelection(true);
    QCOMPARE(withAutoCorrector, withoutAutoCorrector);
}

void AutoCorrectionTextEditTest::shouldNotDeleteAutoCorrectionProvidedByCaller()
{
    QTextEdit richtext;
    auto corrector = new AutoCorrector(&richtext);
    auto autocorrection = new TextAutoCorrectionCore::AutoCorrection();
    corrector->setAutocorrection(autocorrection);
    QCOMPARE(corrector->autocorrection(), autocorrection);
    // Assigning the very same instance again must not delete it: it belongs to the caller.
    corrector->setAutocorrection(autocorrection);
    QCOMPARE(corrector->autocorrection(), autocorrection);
    delete corrector;
    QVERIFY(autocorrection->autoCorrectionSettings() != nullptr);
    delete autocorrection;
}

QTEST_MAIN(AutoCorrectionTextEditTest)

#include "moc_autocorrectiontextedittest.cpp"
