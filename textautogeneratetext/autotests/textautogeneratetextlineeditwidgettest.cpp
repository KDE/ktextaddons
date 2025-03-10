/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextlineeditwidgettest.h"
#include "widgets/textautogeneratetextlineedit.h"
#include "widgets/textautogeneratetextlineeditwidget.h"

#include <QHBoxLayout>
#include <QTest>
QTEST_MAIN(TextAutogenerateTextLineEditWidgetTest)
TextAutogenerateTextLineEditWidgetTest::TextAutogenerateTextLineEditWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutogenerateTextLineEditWidgetTest::shouldHaveDefaultValues()
{
    TextAutogenerateText::TextAutogenerateTextLineEditWidget w;

    auto mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mTextAutogenerateTextLineEdit = w.findChild<TextAutogenerateText::TextAutogenerateTextLineEdit *>(QStringLiteral("mTextAutogenerateTextLineEdit"));
    QVERIFY(mTextAutogenerateTextLineEdit);
}

#include "moc_textautogeneratetextlineeditwidgettest.cpp"
