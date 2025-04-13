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
QTEST_MAIN(TextAutogenerateHistoryWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutogenerateHistoryWidgetTest::TextAutogenerateHistoryWidgetTest(QWidget *parent)
    : QWidget{parent}
{
}

void TextAutogenerateHistoryWidgetTest::shouldHaveDefaultValues()
{
    TextAutogenerateText::TextAutogenerateHistoryWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);

    auto mTextAutogenerateHistoryListView = w.findChild<TextAutogenerateText::TextAutogenerateHistoryListView *>("mTextAutogenerateHistoryListView"_L1);
    QVERIFY(mTextAutogenerateHistoryListView);

    auto mSearchLineEdit = w.findChild<QLineEdit *>("mSearchLineEdit"_L1);
    QVERIFY(mSearchLineEdit);
    QVERIFY(mSearchLineEdit->isClearButtonEnabled());
}

#include "moc_textautogeneratehistorywidgettest.cpp"
