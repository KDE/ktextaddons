/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "emojisortfilterproxymodeltest.h"
using namespace Qt::Literals::StringLiterals;

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
        QCOMPARE(w.emojiToneSuffix(), u"_tone1"_s);
    }
    {
        w.setEmojiTone(TextEmoticonsCore::EmojiModelManager::EmojiTone::MediumLight);
        QCOMPARE(w.emojiToneSuffix(), u"_tone2"_s);
    }
    {
        w.setEmojiTone(TextEmoticonsCore::EmojiModelManager::EmojiTone::Medium);
        QCOMPARE(w.emojiToneSuffix(), u"_tone3"_s);
    }
    {
        w.setEmojiTone(TextEmoticonsCore::EmojiModelManager::EmojiTone::MediumDark);
        QCOMPARE(w.emojiToneSuffix(), u"_tone4"_s);
    }
    {
        w.setEmojiTone(TextEmoticonsCore::EmojiModelManager::EmojiTone::Dark);
        QCOMPARE(w.emojiToneSuffix(), u"_tone5"_s);
    }
}

#include "moc_emojisortfilterproxymodeltest.cpp"
