/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "emojisortfilterproxymodeltest.h"

#include "emojimodel.h"
#include "emojimodelmanager.h"
#include "emojisortfilterproxymodel.h"
#include "unicodeemoticonmanager.h"
#include <QSignalSpy>
#include <QTest>
using namespace Qt::Literals::StringLiterals;

namespace
{
[[nodiscard]] QStringList identifiers(const QAbstractItemModel *model)
{
    QStringList result;
    result.reserve(model->rowCount());
    for (int row = 0, total = model->rowCount(); row < total; ++row) {
        result.append(model->index(row, 0).data(TextEmoticonsCore::EmojiModel::Identifier).toString());
    }
    return result;
}
}
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

void EmojiSortFilterProxyModelTest::shouldChangeCategoryWhenSearching()
{
    TextEmoticonsCore::EmojiSortFilterProxyModel w;
    QSignalSpy categorySpy(&w, &TextEmoticonsCore::EmojiSortFilterProxyModel::categoryChanged);

    w.setCategory(u"people"_s);
    QCOMPARE(w.category(), u"people"_s);
    QCOMPARE(categorySpy.count(), 1);

    w.setSearchIdentifier(u"smile"_s);
    QCOMPARE(w.searchIdentifier(), u"smile"_s);

    // Selecting a category while searching clears the search and applies the new category
    w.setCategory(u"nature"_s);
    QCOMPARE(w.category(), u"nature"_s);
    QVERIFY(w.searchIdentifier().isEmpty());
    QCOMPARE(categorySpy.count(), 2);
}

void EmojiSortFilterProxyModelTest::shouldSearchInAliases()
{
    TextEmoticonsCore::EmojiModel model;
    model.setUnicodeEmoticonList(TextEmoticonsCore::UnicodeEmoticonManager::self()->unicodeEmojiList());

    TextEmoticonsCore::EmojiSortFilterProxyModel w;
    w.setSourceModel(&model);
    w.setCategory(u"activity"_s);

    // :party: is how emojibase names it; :tada: is the name it had before and is now an alias.
    w.setSearchIdentifier(u"party"_s);
    QVERIFY(identifiers(&w).contains(u":party:"_s));

    w.setSearchIdentifier(u"tada"_s);
    QVERIFY(identifiers(&w).contains(u":party:"_s));

    w.setSearchIdentifier(u"TADA"_s);
    QVERIFY(identifiers(&w).contains(u":party:"_s));
}

void EmojiSortFilterProxyModelTest::shouldFilterMixedSkinTones()
{
    TextEmoticonsCore::EmojiModel model;
    model.setUnicodeEmoticonList(TextEmoticonsCore::UnicodeEmoticonManager::self()->unicodeEmojiList());

    TextEmoticonsCore::EmojiSortFilterProxyModel w;
    w.setSourceModel(&model);
    w.setCategory(u"people"_s);
    w.setEmojiTone(TextEmoticonsCore::EmojiModelManager::EmojiTone::Light);

    const QStringList shown = identifiers(&w);
    QVERIFY(shown.contains(u":+1_tone1:"_s));
    // The emoji a tone was picked for is replaced by its variant...
    QVERIFY(!shown.contains(u":+1:"_s));
    // ... and an emoji holding two different tones belongs to no single tone.
    QVERIFY(!shown.contains(u":handshake_tone1-2:"_s));
    QVERIFY(shown.contains(u":handshake_tone1:"_s));
}

#include "moc_emojisortfilterproxymodeltest.cpp"
