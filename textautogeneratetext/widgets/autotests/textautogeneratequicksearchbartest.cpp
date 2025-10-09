/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratequicksearchbartest.h"
#include "widgets/view/textautogeneratequicksearchbar.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTest>
#include <QToolButton>
QTEST_MAIN(TextAutoGenerateQuickSearchBarTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateQuickSearchBarTest::TextAutoGenerateQuickSearchBarTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateQuickSearchBarTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateQuickSearchBar w;

    auto mainLayout = w.findChild<QHBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mSearchLineEdit = w.findChild<QLineEdit *>(u"mSearchLineEdit"_s);
    QVERIFY(mSearchLineEdit);
    QVERIFY(mSearchLineEdit->isClearButtonEnabled());
    QVERIFY(mSearchLineEdit->text().isEmpty());
    QVERIFY(!mSearchLineEdit->placeholderText().isEmpty());

    auto mNextButton = w.findChild<QToolButton *>(u"mNextButton"_s);
    QVERIFY(mNextButton);
    QVERIFY(mNextButton->autoRaise());
    QVERIFY(!mNextButton->toolTip().isEmpty());

    auto mPreviousButton = w.findChild<QToolButton *>(u"mPreviousButton"_s);
    QVERIFY(mPreviousButton);
    QVERIFY(mPreviousButton->autoRaise());
    QVERIFY(!mPreviousButton->toolTip().isEmpty());
}

#include "moc_textautogeneratequicksearchbartest.cpp"
