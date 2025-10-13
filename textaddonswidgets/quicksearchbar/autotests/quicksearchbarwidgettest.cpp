/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "quicksearchbarwidgettest.h"
#include "quicksearchbar/quicksearchbar.h"
#include "quicksearchbar/quicksearchbarwidget.h"
#include <QLineEdit>
#include <QSignalSpy>
#include <QTest>
#include <QVBoxLayout>
#include <TextAddonsWidgets/SlideContainer>
QTEST_MAIN(QuickSearchBarWidgetTest)
using namespace Qt::Literals::StringLiterals;
QuickSearchBarWidgetTest::QuickSearchBarWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void QuickSearchBarWidgetTest::shouldHaveDefaultValues()
{
    TextAddonsWidgets::QuickSearchBarWidget w;

    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mSliderContainer = w.findChild<TextAddonsWidgets::SlideContainer *>(u"mSliderContainer"_s);
    QVERIFY(mSliderContainer);
    auto mQuickSearchBar = w.findChild<TextAddonsWidgets::QuickSearchBar *>(u"mQuickSearchBar"_s);
    QVERIFY(mQuickSearchBar);
}

void QuickSearchBarWidgetTest::shouldEmitSearchTextRequested()
{
    TextAddonsWidgets::QuickSearchBarWidget w;
    auto mQuickSearchBar = w.findChild<TextAddonsWidgets::QuickSearchBar *>(u"mQuickSearchBar"_s);
    auto mSearchLineEdit = mQuickSearchBar->findChild<QLineEdit *>(u"mSearchLineEdit"_s);

    QSignalSpy spy(&w, &TextAddonsWidgets::QuickSearchBarWidget::searchTextRequested);

    mSearchLineEdit->setText(u"foo"_s);
    QCOMPARE(spy.count(), 1);

    mSearchLineEdit->clear();
    QCOMPARE(spy.count(), 2);

    mSearchLineEdit->setText(u"bla"_s);
    QCOMPARE(spy.count(), 3);

    mSearchLineEdit->setText(u"bla"_s);
    QCOMPARE(spy.count(), 3);
}

#include "moc_quicksearchbarwidgettest.cpp"
