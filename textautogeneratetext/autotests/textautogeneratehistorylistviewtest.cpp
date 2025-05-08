/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratehistorylistviewtest.h"
#include "widgets/view/textautogeneratehistorylistview.h"
#include <QTest>
QTEST_MAIN(TextAutoGenerateHistoryListViewTest)

TextAutoGenerateHistoryListViewTest::TextAutoGenerateHistoryListViewTest(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateHistoryListViewTest::~TextAutoGenerateHistoryListViewTest() = default;

void TextAutoGenerateHistoryListViewTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateHistoryListView w;
    QVERIFY(!w.dragEnabled());
    QCOMPARE(w.indentation(), 0);
    QVERIFY(!w.rootIsDecorated());
    QVERIFY(w.itemsExpandable());
    QCOMPARE(w.horizontalScrollBarPolicy(), Qt::ScrollBarAlwaysOff);
    QVERIFY(w.isHeaderHidden());
}

#include "moc_textautogeneratehistorylistviewtest.cpp"
