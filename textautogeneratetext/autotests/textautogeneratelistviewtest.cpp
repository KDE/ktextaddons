/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratelistviewtest.h"
#include "widgets/view/textautogeneratelistview.h"
#include <QTest>

QTEST_MAIN(TextAutogenerateListViewTest);

TextAutogenerateListViewTest::TextAutogenerateListViewTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutogenerateListViewTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutogenerateListView w;
    QCOMPARE(w.verticalScrollMode(), QAbstractItemView::ScrollPerPixel);
}

#include "moc_textautogeneratelistviewtest.cpp"
