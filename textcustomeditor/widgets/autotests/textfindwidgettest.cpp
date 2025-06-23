/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textfindwidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "widgets/textfindreplacewidget.h"
#include <QPushButton>
#include <QTest>
QTEST_MAIN(TextFindWidgetTest)
TextFindWidgetTest::TextFindWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextFindWidgetTest::shouldHaveDefaultValues()
{
    TextCustomEditor::TextFindWidget w;
    QVERIFY(w.searchLineEdit());
    QVERIFY(!w.isRegularExpression());
    QVERIFY(w.searchText().isEmpty());

    auto mFindNextBtn = w.findChild<QPushButton *>(u"mFindNextBtn"_s);
    QVERIFY(mFindNextBtn);
    QVERIFY(!mFindNextBtn->text().isEmpty());
    QVERIFY(!mFindNextBtn->toolTip().isEmpty());
    QVERIFY(!mFindNextBtn->isEnabled());

    auto mFindPrevBtn = w.findChild<QPushButton *>(u"mFindPrevBtn"_s);
    QVERIFY(mFindPrevBtn);
    QVERIFY(!mFindPrevBtn->text().isEmpty());
    QVERIFY(!mFindPrevBtn->toolTip().isEmpty());
    QVERIFY(!mFindPrevBtn->isEnabled());

    auto optionsBtn = w.findChild<QPushButton *>(u"optionsBtn"_s);
    QVERIFY(optionsBtn);
    QVERIFY(!optionsBtn->text().isEmpty());
    QVERIFY(!optionsBtn->toolTip().isEmpty());
    QVERIFY(optionsBtn->isEnabled());
}

#include "moc_textfindwidgettest.cpp"
