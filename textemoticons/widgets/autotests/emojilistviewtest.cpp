/*
  SPDX-FileCopyrightText: 2021-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emojilistviewtest.h"
using namespace Qt::Literals::StringLiterals;

#include "emojilistview.h"
#include <QTest>
QTEST_MAIN(EmojiListViewTest)
EmojiListViewTest::EmojiListViewTest(QObject *parent)
    : QObject(parent)
{
}

void EmojiListViewTest::shouldHaveDefaultValues()
{
    TextEmoticonsWidgets::EmojiListView w;
    QCOMPARE(w.viewMode(), QListView::IconMode);
    QCOMPARE(w.horizontalScrollBarPolicy(), Qt::ScrollBarAlwaysOff);
    // QVERIFY(w.uniformItemSizes());
    QVERIFY(!w.dragEnabled());
    QVERIFY(w.hasMouseTracking());
    QCOMPARE(w.contextMenuPolicy(), Qt::DefaultContextMenu);
    QCOMPARE(w.itemDelegate()->objectName(), u"emoticonDelegate"_s);
}

#include "moc_emojilistviewtest.cpp"
