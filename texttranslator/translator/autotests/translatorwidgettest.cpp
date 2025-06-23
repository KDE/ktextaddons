/*
  SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatorwidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "translator/widgets/translatorwidget.h"

#include <QPushButton>

#include <QComboBox>
#include <QSignalSpy>
#include <QStandardPaths>
#include <QTest>
#include <QToolButton>
#include <qtestkeyboard.h>
#include <qtestmouse.h>
QTEST_MAIN(TranslatorWidgetTest)

TranslatorWidgetTest::TranslatorWidgetTest()
{
    QStandardPaths::setTestModeEnabled(true);
}

void TranslatorWidgetTest::shouldHaveDefaultValuesOnCreation()
{
    TextTranslator::TranslatorWidget edit;
    auto from = edit.findChild<QComboBox *>(u"from"_s);
    auto to = edit.findChild<QComboBox *>(u"to"_s);

    auto inputtext = edit.findChild<TextTranslator::TranslatorTextEdit *>(u"inputtext"_s);
    auto translate = edit.findChild<QPushButton *>(u"translate-button"_s);
    auto clear = edit.findChild<QPushButton *>(u"clear-button"_s);
    auto invert = edit.findChild<QPushButton *>(u"invert-button"_s);
    auto configure = edit.findChild<QToolButton *>(u"configure_button"_s);
    auto close = edit.findChild<QToolButton *>(u"close-button"_s);
    QVERIFY(configure);
    QVERIFY(close);
    QVERIFY(invert);
    QVERIFY(clear);
    QVERIFY(translate);
    QVERIFY(from);
    QVERIFY(to);
    QCOMPARE(from->count() > 0, true);
    QCOMPARE(to->count() > 0, true);
    QVERIFY(inputtext);
    QCOMPARE(inputtext->toPlainText(), QString());
    QCOMPARE(translate->isEnabled(), false);
}

void TranslatorWidgetTest::shouldEnableTranslateButtonWhenTextToTranslateIsNotEmpty()
{
    TextTranslator::TranslatorWidget edit;

    auto inputtext = edit.findChild<TextTranslator::TranslatorTextEdit *>(u"inputtext"_s);
    auto translate = edit.findChild<QPushButton *>(u"translate-button"_s);
    inputtext->setPlainText(u"Foo"_s);
    QCOMPARE(translate->isEnabled(), true);
}

void TranslatorWidgetTest::shouldDisableTranslateButtonAndClearTextWhenClickOnClearButton()
{
    TextTranslator::TranslatorWidget edit;
    auto inputtext = edit.findChild<TextTranslator::TranslatorTextEdit *>(u"inputtext"_s);
    auto translate = edit.findChild<QPushButton *>(u"translate-button"_s);
    inputtext->setPlainText(u"Foo"_s);
    auto clear = edit.findChild<QPushButton *>(u"clear-button"_s);
    QTest::mouseClick(clear, Qt::LeftButton);
    QCOMPARE(inputtext->toPlainText(), QString());
    QCOMPARE(translate->isEnabled(), false);
}

void TranslatorWidgetTest::shouldInvertLanguageWhenClickOnInvertButton()
{
    TextTranslator::TranslatorWidget edit;
    auto from = edit.findChild<QComboBox *>(u"from"_s);
    auto to = edit.findChild<QComboBox *>(u"to"_s);

    const int fromIndex = 5;
    const int toIndex = 7;
    from->setCurrentIndex(fromIndex);
    to->setCurrentIndex(toIndex);
    auto invert = edit.findChild<QPushButton *>(u"invert-button"_s);
    QTest::mouseClick(invert, Qt::LeftButton);
    const int newFromIndex = from->currentIndex();
    const int newToIndex = to->currentIndex();
    QCOMPARE(fromIndex != newFromIndex, true);
    QCOMPARE(toIndex != newToIndex, true);
}

void TranslatorWidgetTest::shouldHideWidgetWhenPressEscape()
{
    TextTranslator::TranslatorWidget edit;
    edit.show();
    QVERIFY(QTest::qWaitForWindowExposed(&edit));
    QTest::keyPress(&edit, Qt::Key_Escape);
    QCOMPARE(edit.isVisible(), false);
}

void TranslatorWidgetTest::shouldEmitTranslatorWasClosedSignalWhenCloseIt()
{
    TextTranslator::TranslatorWidget edit;
    edit.show();
    QVERIFY(QTest::qWaitForWindowExposed(&edit));
    QSignalSpy spy(&edit, &TextTranslator::TranslatorWidget::toolsWasClosed);
    QTest::keyClick(&edit, Qt::Key_Escape);
    QCOMPARE(spy.count(), 1);
}

#include "moc_translatorwidgettest.cpp"
