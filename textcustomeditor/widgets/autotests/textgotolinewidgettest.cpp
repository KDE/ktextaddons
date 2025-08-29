/*
   SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textgotolinewidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "widgets/textgotolinewidget.h"
#include <QPushButton>
#include <QSignalSpy>
#include <QSpinBox>
#include <QTest>
#include <QToolButton>
#include <qtestkeyboard.h>
#include <qtestmouse.h>

TextGoToLineWidgetTest::TextGoToLineWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void TextGoToLineWidgetTest::shouldHaveDefaultValuesOnCreation()
{
    TextCustomEditor::TextGoToLineWidget edit;
    edit.show();
    QVERIFY(QTest::qWaitForWindowExposed(&edit));
    auto line = edit.findChild<QSpinBox *>(u"line"_s);
    QVERIFY(line);
    QCOMPARE(line->minimum(), 1);
    auto gotolinebutton = edit.findChild<QPushButton *>(u"gotoline"_s);
    QVERIFY(gotolinebutton);
    auto closebutton = edit.findChild<QToolButton *>(u"closebutton"_s);
    QVERIFY(closebutton);
    QVERIFY(line->hasFocus());
}

void TextGoToLineWidgetTest::shouldEmitGoToLineSignalWhenPressOnButton()
{
    TextCustomEditor::TextGoToLineWidget edit;
    auto gotolinebutton = edit.findChild<QPushButton *>(u"gotoline"_s);
    QSignalSpy spy(&edit, &TextCustomEditor::TextGoToLineWidget::moveToLine);
    QTest::mouseClick(gotolinebutton, Qt::LeftButton);
    QCOMPARE(spy.count(), 1);
}

void TextGoToLineWidgetTest::shouldEmitGoToLineSignalCorrectValueWhenPressOnButton()
{
    TextCustomEditor::TextGoToLineWidget edit;
    auto gotolinebutton = edit.findChild<QPushButton *>(u"gotoline"_s);
    auto line = edit.findChild<QSpinBox *>(u"line"_s);
    line->setValue(5);
    QCOMPARE(line->value(), 5);
    QSignalSpy spy(&edit, &TextCustomEditor::TextGoToLineWidget::moveToLine);
    QTest::mouseClick(gotolinebutton, Qt::LeftButton);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toInt(), 5);
}

void TextGoToLineWidgetTest::shouldHideWidgetWhenClickOnCloseButton()
{
    TextCustomEditor::TextGoToLineWidget edit;
    edit.show();
    QVERIFY(QTest::qWaitForWindowExposed(&edit));
    QVERIFY(edit.isVisible());
    auto closebutton = edit.findChild<QToolButton *>(u"closebutton"_s);
    QTest::mouseClick(closebutton, Qt::LeftButton);
    QVERIFY(!edit.isVisible());
}

void TextGoToLineWidgetTest::shouldHideWidgetWhenPressEscape()
{
    TextCustomEditor::TextGoToLineWidget edit;
    edit.show();
    QVERIFY(QTest::qWaitForWindowExposed(&edit));
    QTest::keyPress(&edit, Qt::Key_Escape);
    QCOMPARE(edit.isVisible(), false);
}

void TextGoToLineWidgetTest::shouldEmitGoToLineSignalWhenSpinboxHasFocusAndWePressEnter()
{
    TextCustomEditor::TextGoToLineWidget edit;
    edit.show();
    QVERIFY(QTest::qWaitForWindowExposed(&edit));
    auto line = edit.findChild<QSpinBox *>(u"line"_s);
    line->setFocus();
    QVERIFY(line->hasFocus());
    line->setValue(5);
    QSignalSpy spy(&edit, &TextCustomEditor::TextGoToLineWidget::moveToLine);
    QTest::keyPress(line, Qt::Key_Enter);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toInt(), 5);
}

void TextGoToLineWidgetTest::shouldHasFocusEachTimeThatItShown()
{
    TextCustomEditor::TextGoToLineWidget edit;
    edit.show();
    QVERIFY(QTest::qWaitForWindowExposed(&edit));
    auto line = edit.findChild<QSpinBox *>(u"line"_s);
    QVERIFY(line);
    QVERIFY(line->hasFocus());
    edit.hide();
    QVERIFY(!line->hasFocus());
    edit.show();
    QVERIFY(QTest::qWaitForWindowExposed(&edit));
    // FIXME QVERIFY(line->hasFocus());
}

void TextGoToLineWidgetTest::shouldSetFocusWhenWeRecallGotToLine()
{
    TextCustomEditor::TextGoToLineWidget edit;
    edit.show();
    QVERIFY(QTest::qWaitForWindowExposed(&edit));
    auto line = edit.findChild<QSpinBox *>(u"line"_s);
    QVERIFY(line->hasFocus());
    edit.setFocus();
    QVERIFY(!line->hasFocus());
    edit.goToLine();
    QVERIFY(line->hasFocus());
}

void TextGoToLineWidgetTest::shouldChangeMaximumValue()
{
    TextCustomEditor::TextGoToLineWidget edit;
    edit.show();
    QVERIFY(QTest::qWaitForWindowExposed(&edit));
    auto line = edit.findChild<QSpinBox *>(u"line"_s);

    QCOMPARE(line->value(), 1);
    QCOMPARE(line->minimum(), 1);

    edit.setMaximumLineCount(50);
    QCOMPARE(line->value(), 1);
    QCOMPARE(line->minimum(), 1);
    QCOMPARE(line->maximum(), 50);

    edit.setMaximumLineCount(10);
    QCOMPARE(line->value(), 1);
    QCOMPARE(line->minimum(), 1);
    QCOMPARE(line->maximum(), 10);
}

QTEST_MAIN(TextGoToLineWidgetTest)

#include "moc_textgotolinewidgettest.cpp"
