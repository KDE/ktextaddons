/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratelistviewtest.h"
#include "widgets/view/textautogeneratelistview.h"
#include <QTest>

QTEST_MAIN(TextAutoGenerateListViewTest);

TextAutoGenerateListViewTest::TextAutoGenerateListViewTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateListViewTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateListView w(nullptr);
    QCOMPARE(w.verticalScrollMode(), QAbstractItemView::ScrollPerPixel);
}

#include "moc_textautogeneratelistviewtest.cpp"
