/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratesearchwidgettest.h"
#include "widgets/textautogeneratesearchwidget.h"
#include "widgets/view/textautogeneratesearchlistview.h"
#include <QLineEdit>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateSearchWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateSearchWidgetTest::TextAutoGenerateSearchWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateSearchWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateSearchWidget w(nullptr);

    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mTextAutoGenerateSearchListView = w.findChild<TextAutoGenerateText::TextAutoGenerateSearchListView *>(u"mTextAutoGenerateSearchListView"_s);
    QVERIFY(mTextAutoGenerateSearchListView);

    auto mSearchLineEdit = w.findChild<QLineEdit *>("mSearchLineEdit"_L1);
    QVERIFY(mSearchLineEdit);
    QVERIFY(mSearchLineEdit->isClearButtonEnabled());
    QVERIFY(!mSearchLineEdit->placeholderText().isEmpty());
}

#include "moc_textautogeneratesearchwidgettest.cpp"
