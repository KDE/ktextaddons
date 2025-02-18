/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "emojisortfilterproxymodeltest.h"
#include "emojimodelmanager.h"
#include "emojisortfilterproxymodel.h"
#include <QTest>
QTEST_GUILESS_MAIN(EmojiSortFilterProxyModelTest)
EmojiSortFilterProxyModelTest::EmojiSortFilterProxyModelTest(QObject *parent)
    : QObject{parent}
{
}

void EmojiSortFilterProxyModelTest::shouldHaveDefaultValues()
{
    TextEmoticonsCore::EmojiSortFilterProxyModel w;

    QVERIFY(w.category().isEmpty());
    QVERIFY(w.recentEmoticons().isEmpty());
    QVERIFY(w.searchIdentifier().isEmpty());
    QCOMPARE(w.emojiTone(), TextEmoticonsCore::EmojiModelManager::EmojiTone::All);
    QCOMPARE(w.emojiToneSuffix(), QString());
}

void EmojiSortFilterProxyModelTest::shouldHaveToneSuffix()
{
    TextEmoticonsCore::EmojiSortFilterProxyModel w;
    {
        w.setEmojiTone(TextEmoticonsCore::EmojiModelManager::EmojiTone::Original);
        QCOMPARE(w.emojiToneSuffix(), QString());
    }
    {
        w.setEmojiTone(TextEmoticonsCore::EmojiModelManager::EmojiTone::Light);
        QCOMPARE(w.emojiToneSuffix(), QStringLiteral("_tone1"));
    }
    {
        w.setEmojiTone(TextEmoticonsCore::EmojiModelManager::EmojiTone::MediumLight);
        QCOMPARE(w.emojiToneSuffix(), QStringLiteral("_tone2"));
    }
    {
        w.setEmojiTone(TextEmoticonsCore::EmojiModelManager::EmojiTone::Medium);
        QCOMPARE(w.emojiToneSuffix(), QStringLiteral("_tone3"));
    }
    {
        w.setEmojiTone(TextEmoticonsCore::EmojiModelManager::EmojiTone::MediumDark);
        QCOMPARE(w.emojiToneSuffix(), QStringLiteral("_tone4"));
    }
    {
        w.setEmojiTone(TextEmoticonsCore::EmojiModelManager::EmojiTone::Dark);
        QCOMPARE(w.emojiToneSuffix(), QStringLiteral("_tone5"));
    }
}

#include "moc_emojisortfilterproxymodeltest.cpp"
