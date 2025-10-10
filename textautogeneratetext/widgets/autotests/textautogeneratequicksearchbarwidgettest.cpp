/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratequicksearchbarwidgettest.h"
#include "widgets/view/textautogeneratequicksearchbar.h"
#include "widgets/view/textautogeneratequicksearchbarwidget.h"
#include <QTest>
#include <TextAddonsWidgets/SlideContainer>
#include <qboxlayout.h>
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

#include "moc_textautogeneratequicksearchbarwidgettest.cpp"
