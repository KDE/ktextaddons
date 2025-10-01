/*
   SPDX-FileCopyrightText: 2020-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "unicodeemoticonmanager.h"

#include "textemoticonscore_debug.h"
#include "unicodeemoticonparser.h"
#include <KLocalizedString>

#include <QFile>
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

UnicodeEmoticonManager::UnicodeEmoticonManager(QObject *parent)
    : QObject(parent)
    , d(new TextEmoticonsCore::UnicodeEmoticonManagerPrivate)
{
    d->loadUnicodeEmoji();
}

UnicodeEmoticonManager::UnicodeEmoticonManager(const QString &filename, QObject *parent)
    : QObject(parent)
    , d(new TextEmoticonsCore::UnicodeEmoticonManagerPrivate)
{
    d->loadUnicodeEmoji(filename);
}

UnicodeEmoticonManager::~UnicodeEmoticonManager() = default;

UnicodeEmoticonManager *UnicodeEmoticonManager::self()
{
    static UnicodeEmoticonManager s_self;
    return &s_self;
}

void UnicodeEmoticonManager::loadUnicodeEmoji(const QString &filename)
{
    d->loadUnicodeEmoji(filename);
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
        const QString category = emo.category();
        if (!seen.contains(category)) {
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

    auto hasRequestedCategory = [category](const UnicodeEmoticon &emo) {
        return emo.category() == category;
    };
    std::copy_if(d->unicodeEmojiList.begin(), d->unicodeEmojiList.end(), std::back_inserter(result), hasRequestedCategory);
    return result;
}

UnicodeEmoticon UnicodeEmoticonManager::unicodeEmoticonForEmoji(const QString &emojiIdentifier) const
{
    for (const UnicodeEmoticon &emo : d->unicodeEmojiList) {
        if (emo.hasEmoji(emojiIdentifier)) {
            return emo;
        }
    }
    return {};
}

#include "moc_unicodeemoticonmanager.cpp"
