/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratesearchwidgettest.h"
#include "widgets/textautogeneratesearchwidget.h"
#include "widgets/view/textautogeneratesearchlistview.h"
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateSearchWidgetTest)

TextAutoGenerateSearchWidgetTest::TextAutoGenerateSearchWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateSearchWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateSearchWidget w;

    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mTextAutoGenerateSearchListView =
        w.findChild<TextAutoGenerateText::TextAutoGenerateSearchListView *>(QStringLiteral("mTextAutoGenerateSearchListView"));
    QVERIFY(mTextAutoGenerateSearchListView);
}

#include "moc_textautogeneratesearchwidgettest.cpp"
