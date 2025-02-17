/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "emojiproxymodeltest.h"
#include "emojisortfilterproxymodel.h"
#include <QTest>
QTEST_GUILESS_MAIN(EmojiProxyModelTest)
EmojiProxyModelTest::EmojiProxyModelTest(QObject *parent)
    : QObject{parent}
{
}

void EmojiProxyModelTest::shouldHaveDefaultValues()
{
    TextEmoticonsCore::EmojiSortFilterProxyModel w;

    QVERIFY(w.category().isEmpty());
    QVERIFY(w.recentEmoticons().isEmpty());
    QVERIFY(w.searchIdentifier().isEmpty());
}

#include "moc_emojiproxymodeltest.cpp"
