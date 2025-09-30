/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "emojicategorybuttontest.h"
#include "emojicategorybutton.h"
#include <QTest>
QTEST_MAIN(EmojiCategoryButtonTest)
EmojiCategoryButtonTest::EmojiCategoryButtonTest(QObject *parent)
    : QObject{parent}
{
}

void EmojiCategoryButtonTest::shouldHaveDefaultValues()
{
    TextEmoticonsWidgets::EmojiCategoryButton w;
    QVERIFY(w.isCheckable());
    QVERIFY(w.autoRaise());
}

#include "moc_emojicategorybuttontest.cpp"
