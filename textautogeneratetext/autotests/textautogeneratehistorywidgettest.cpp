/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratehistorywidgettest.h"
#include "widgets/textautogeneratehistorywidget.h"
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutogenerateHistoryWidgetTest)

TextAutogenerateHistoryWidgetTest::TextAutogenerateHistoryWidgetTest(QWidget *parent)
    : QWidget{parent}
{
}

void TextAutogenerateHistoryWidgetTest::shouldHaveDefaultValues()
{
    TextAutogenerateText::TextAutogenerateHistoryWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    // TODO
}

#include "moc_textautogeneratehistorywidgettest.cpp"
