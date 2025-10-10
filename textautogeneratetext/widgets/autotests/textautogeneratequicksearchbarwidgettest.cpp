/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratequicksearchbarwidgettest.h"
#include "widgets/view/textautogeneratequicksearchbar.h"
#include "widgets/view/textautogeneratequicksearchbarwidget.h"
#include <QLineEdit>
#include <QSignalSpy>
#include <QTest>
#include <QVBoxLayout>
#include <TextAddonsWidgets/SlideContainer>
QTEST_MAIN(TextAutoGenerateQuickSearchBarWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateQuickSearchBarWidgetTest::TextAutoGenerateQuickSearchBarWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateQuickSearchBarWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateQuickSearchBarWidget w;

    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mSliderContainer = w.findChild<TextAddonsWidgets::SlideContainer *>(u"mSliderContainer"_s);
    QVERIFY(mSliderContainer);
    auto mQuickSearchBar = w.findChild<TextAutoGenerateText::TextAutoGenerateQuickSearchBar *>(u"mQuickSearchBar"_s);
    QVERIFY(mQuickSearchBar);
}

void TextAutoGenerateQuickSearchBarWidgetTest::shouldEmitSearchTextRequested()
{
    TextAutoGenerateText::TextAutoGenerateQuickSearchBarWidget w;
    auto mQuickSearchBar = w.findChild<TextAutoGenerateText::TextAutoGenerateQuickSearchBar *>(u"mQuickSearchBar"_s);
    auto mSearchLineEdit = mQuickSearchBar->findChild<QLineEdit *>(u"mSearchLineEdit"_s);

    QSignalSpy spy(&w, &TextAutoGenerateText::TextAutoGenerateQuickSearchBarWidget::searchTextRequested);

    mSearchLineEdit->setText(u"foo"_s);
    QCOMPARE(spy.count(), 1);

    mSearchLineEdit->clear();
    QCOMPARE(spy.count(), 2);

    mSearchLineEdit->setText(u"bla"_s);
    QCOMPARE(spy.count(), 3);

    mSearchLineEdit->setText(u"bla"_s);
    QCOMPARE(spy.count(), 3);
}

#include "moc_textautogeneratequicksearchbarwidgettest.cpp"
