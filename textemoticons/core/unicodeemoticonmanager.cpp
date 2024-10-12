/*
   SPDX-FileCopyrightText: 2020-2025 Laurent Montel <montel@kde.org>
   SPDX-FileCopyrightText: 2022 Weng Xuetian <wegnxt@gmail.com>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "unicodeemoticonmanager.h"

#include <QStandardPaths>
#include <emojicategory.h>

#include "textemoticonscore_debug.h"
#include "unicodeemoticonparser.h"
#include <KLocalizedString>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <ranges>
using namespace Qt::Literals::StringLiterals;
using namespace TextEmoticonsCore;
class TextEmoticonsCore::UnicodeEmoticonManagerPrivate
{
public:
    void loadUnicodeEmoji();
    [[nodiscard]] QString i18nUnicodeCategory(const QString &name) const;
    QList<UnicodeEmoticon> unicodeEmojiList;
};

void UnicodeEmoticonManagerPrivate::loadUnicodeEmoji()
{
    const QHash<QString, QString> specialCases{{QLatin1String{"zh-TW"}, QLatin1String{"zh_Hant"}}, {QLatin1String{"zh-HK"}, QLatin1String{"zh_Hant_HK"}}};
    QLocale locale;
    QStringList dicts;
    auto bcp = locale.bcp47Name();
    bcp = specialCases.value(bcp, bcp);
    bcp.replace(QLatin1Char('-'), QLatin1Char('_'));

    const QString dictName = QLatin1String{"kf6/emoji/"} + bcp + QLatin1String{".dict"};
    const QString path = QStandardPaths::locate(QStandardPaths::GenericDataLocation, dictName);
    if (!path.isEmpty()) {
        dicts << path;
    }

    for (qsizetype underscoreIndex = -1; (underscoreIndex = bcp.lastIndexOf(QLatin1Char('_'), underscoreIndex)) != -1; --underscoreIndex) {
        const QString genericDictName = QLatin1String{"kf6/emoji/"} + QStringView(bcp).left(underscoreIndex) + QLatin1String{".dict"};
        const QString genericPath = QStandardPaths::locate(QStandardPaths::GenericDataLocation, genericDictName);

        if (!genericPath.isEmpty()) {
            dicts << genericPath;
        }
    }

    // Always fallback to en, because some annotation data only have minimum data.
    const QString genericPath = QStandardPaths::locate(QStandardPaths::GenericDataLocation, QStringLiteral("kf6/emoji/en.dict"));

    if (!QFile::exists(genericPath)) {
        qCWarning(TEXTEMOTICONSCORE_LOG) << "Could not find emoji dictionaries.";
        return;
    }

    // We load in reverse order, because we want to preserve the order.
    for (const auto &dict : std::ranges::reverse_view(dicts)) {
        UnicodeEmoticonParser unicodeParser;
        for (const auto &emoji : unicodeParser.parse(dict)) {
            if (!unicodeEmojiList.contains(emoji)) {
                unicodeEmojiList.append(emoji);
            }
        }
    }

    // Load fallback English unicode emojis
    UnicodeEmoticonParser unicodeParser;
    for (const auto &emoji : unicodeParser.parse(genericPath)) {
        const auto index = unicodeEmojiList.indexOf(emoji);
        if (index == -1) {
            unicodeEmojiList.append(emoji);
        } else {
            // If it is found, we want to always set the identifier to it's English counterpart
            unicodeEmojiList[index].setIdentifier(emoji.identifier());
        }
    }
}

QString UnicodeEmoticonManagerPrivate::i18nUnicodeCategory(const QString &name) const
{
    if (qsizetype index = getCategoryNames().indexOf(name); index != -1)
        return geti18nCategoryNames()[index];
    else
        return {};
}

UnicodeEmoticonManager::UnicodeEmoticonManager(QObject *parent)
    : QObject(parent)
    , d(new TextEmoticonsCore::UnicodeEmoticonManagerPrivate)
{
    d->loadUnicodeEmoji();
}

UnicodeEmoticonManager::~UnicodeEmoticonManager() = default;

UnicodeEmoticonManager *UnicodeEmoticonManager::self()
{
    static UnicodeEmoticonManager s_self;
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
