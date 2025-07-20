/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratehistorywidgettest.h"
#include "widgets/textautogeneratehistorywidget.h"
#include "widgets/view/textautogeneratehistorylistview.h"
#include <QLineEdit>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateHistoryWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateHistoryWidgetTest::TextAutoGenerateHistoryWidgetTest(QWidget *parent)
    : QWidget{parent}
{
}

void TextAutoGenerateHistoryWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateHistoryWidget w(nullptr);
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto mTextAutoGenerateHistoryListView = w.findChild<TextAutoGenerateText::TextAutoGenerateHistoryListView *>("mTextAutoGenerateHistoryListView"_L1);
    QVERIFY(mTextAutoGenerateHistoryListView);

    auto mSearchLineEdit = w.findChild<QLineEdit *>("mSearchLineEdit"_L1);
    QVERIFY(mSearchLineEdit);
    QVERIFY(mSearchLineEdit->isClearButtonEnabled());
    QVERIFY(!mSearchLineEdit->placeholderText().isEmpty());
}

#include "moc_textautogeneratehistorywidgettest.cpp"
