/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "quicksearchbartest.h"
#include "quicksearchbar/quicksearchbar.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSignalSpy>
#include <QTest>
#include <QToolButton>
QTEST_MAIN(QuickSearchBarTest)
using namespace Qt::Literals::StringLiterals;
QuickSearchBarTest::QuickSearchBarTest(QObject *parent)
    : QObject{parent}
{
}

void QuickSearchBarTest::shouldHaveDefaultValues()
{
    TextAddonsWidgets::QuickSearchBar w;

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
    QVERIFY(!mNextButton->isEnabled());

    auto mPreviousButton = w.findChild<QToolButton *>(u"mPreviousButton"_s);
    QVERIFY(mPreviousButton);
    QVERIFY(mPreviousButton->autoRaise());
    QVERIFY(!mPreviousButton->toolTip().isEmpty());
    QVERIFY(!mPreviousButton->isEnabled());
}

void QuickSearchBarTest::shouldEmitSearchTextRequested()
{
    TextAddonsWidgets::QuickSearchBar w;
    auto mSearchLineEdit = w.findChild<QLineEdit *>(u"mSearchLineEdit"_s);

    QSignalSpy spy(&w, &TextAddonsWidgets::QuickSearchBar::searchTextRequested);

    mSearchLineEdit->setText(u"foo"_s);
    QCOMPARE(spy.count(), 1);

    mSearchLineEdit->clear();
    QCOMPARE(spy.count(), 2);

    mSearchLineEdit->setText(u"bla"_s);
    QCOMPARE(spy.count(), 3);

    mSearchLineEdit->setText(u"bla"_s);
    QCOMPARE(spy.count(), 3);
}

#include "moc_quicksearchbartest.cpp"
