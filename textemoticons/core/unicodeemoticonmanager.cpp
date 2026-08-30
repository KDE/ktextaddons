/*
   SPDX-FileCopyrightText: 2020-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "unicodeemoticonmanager.h"

#include "textemoticonscore_debug.h"
#include "unicodeemoticonparser.h"
#include <KLocalizedString>

#include <QFile>
#include <QHash>
#include <QJsonDocument>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace TextEmoticonsCore;
class TextEmoticonsCore::UnicodeEmoticonManagerPrivate
{
public:
    void loadUnicodeEmoji(const QString &filename = {});
    [[nodiscard]] QString i18nUnicodeCategory(const QString &name) const;
    QList<UnicodeEmoticon> unicodeEmojiList;
    // Every name an emoji answers to, mapped to its position in unicodeEmojiList, so
    // that looking one up does not walk the whole list comparing aliases.
    QHash<QString, int> emojiIndexes;
};

void UnicodeEmoticonManagerPrivate::loadUnicodeEmoji(const QString &filename)
{
    const UnicodeEmoticonParser unicodeParser;
    QFile file(filename.isEmpty() ? u":/emoji.json"_s : filename);
    if (!file.open(QFile::ReadOnly)) {
        qCWarning(TEXTEMOTICONSCORE_LOG) << "Impossible to open file: " << file.errorString();
        return;
    }
    const QJsonDocument doc = QJsonDocument::fromJson(file.readAll());

    const QJsonObject obj = doc.object();
    unicodeEmojiList = unicodeParser.parse(obj);

    emojiIndexes.clear();
    emojiIndexes.reserve(unicodeEmojiList.count() * 3);
    for (int i = 0, total = unicodeEmojiList.count(); i < total; ++i) {
        const UnicodeEmoticon &emoticon = unicodeEmojiList.at(i);
        // The list is sorted, so on a name claimed twice keep the first emoji, which is
        // the one a search through the list would have stopped on.
        const auto index = [this, i](const QString &name) {
            if (!name.isEmpty()) {
                emojiIndexes.tryEmplace(name, i);
            }
        };
        index(emoticon.identifier());
        index(emoticon.unicode());
        const auto aliases = emoticon.aliases();
        for (const QString &alias : aliases) {
            index(alias);
        }
    }
}

QString UnicodeEmoticonManagerPrivate::i18nUnicodeCategory(const QString &name) const
{
    // Name "🚗"Category "travel", Name "🇿"Category "regional", Name "🏳️"Category "flags")
    if (name == "symbols"_L1) {
        return i18n("Symbols");
    } else if (name == "activity"_L1) {
        return i18n("Activity");
    } else if (name == "objects"_L1) {
        return i18n("Objects");
    } else if (name == "nature"_L1) {
        return i18n("Nature");
    } else if (name == "food"_L1) {
        return i18n("Food");
    } else if (name == "people"_L1) {
        return i18n("People");
    } else if (name == "travel"_L1) {
        return i18n("Travel");
    } else if (name == "regional"_L1) {
        return i18n("Regional");
    } else if (name == "flags"_L1) {
        return i18n("Flags");
    } else {
        qCWarning(TEXTEMOTICONSCORE_LOG) << "Missing i18n translate " << name;
    }
    return {};
}

UnicodeEmoticonManager::UnicodeEmoticonManager(const QString &filename, QObject *parent)
    : QObject(parent)
    , d(new TextEmoticonsCore::UnicodeEmoticonManagerPrivate)
{
    d->loadUnicodeEmoji(filename);
}

UnicodeEmoticonManager::~UnicodeEmoticonManager() = default;

UnicodeEmoticonManager *UnicodeEmoticonManager::self(const QString &filename)
{
    static UnicodeEmoticonManager s_self(filename);
    return &s_self;
}

QList<UnicodeEmoticon> UnicodeEmoticonManager::unicodeEmojiList() const
{
    return d->unicodeEmojiList;
}

int UnicodeEmoticonManager::count() const
{
    return d->unicodeEmojiList.count();
}

QList<EmoticonCategory> UnicodeEmoticonManager::categories() const
{
    QList<EmoticonCategory> categories;
    QSet<QString> seen;
    for (const UnicodeEmoticon &emo : std::as_const(d->unicodeEmojiList)) {
        // Pick the first icon in each category
        if (const QString category = emo.category(); !seen.contains(category)) {
            seen.insert(category);
            if (category == "modifier"_L1) { // pointless icons
                continue;
            }
            EmoticonCategory cat;
            cat.setCategory(category);
            cat.setName(emo.unicode());
            cat.setI18nName(d->i18nUnicodeCategory(category));
            cat.setOrder(UnicodeEmoticonParser::changeOrder(category));
            categories.append(std::move(cat));
        }
    }
    std::sort(categories.begin(), categories.end());
    return categories;
}

QList<UnicodeEmoticon> UnicodeEmoticonManager::emojisForCategory(const QString &category) const
{
    QList<UnicodeEmoticon> result;
    result.reserve(d->unicodeEmojiList.size());

    auto hasRequestedCategory = [category](const UnicodeEmoticon &emo) {
        return emo.category() == category;
    };
    std::copy_if(d->unicodeEmojiList.begin(), d->unicodeEmojiList.end(), std::back_inserter(result), hasRequestedCategory);
    return result;
}

UnicodeEmoticon UnicodeEmoticonManager::unicodeEmoticonForEmoji(const QString &emojiIdentifier) const
{
    const auto it = d->emojiIndexes.constFind(emojiIdentifier);
    if (it == d->emojiIndexes.cend()) {
        return {};
    }
    return d->unicodeEmojiList.at(it.value());
}

#include "moc_unicodeemoticonmanager.cpp"
