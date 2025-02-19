/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "unicodeemoticonparser.h"
#include "textemoticonscore_debug.h"
#include <QJsonArray>
#include <QJsonObject>

#include <algorithm>
using namespace TextEmoticonsCore;
using namespace Qt::Literals::StringLiterals;
UnicodeEmoticonParser::UnicodeEmoticonParser() = default;

UnicodeEmoticonParser::~UnicodeEmoticonParser() = default;

QList<UnicodeEmoticon> UnicodeEmoticonParser::parse(const QJsonObject &o) const
{
    auto aliases = [](const QJsonArray &alternates, const QJsonArray &ascii) {
        QStringList ret;
        ret.reserve(alternates.size() + ascii.size());
        auto convert = [&](const QJsonArray &array) {
            auto toString = [](const QJsonValue &value) {
                return value.toString();
            };
            std::transform(array.begin(), array.end(), std::back_inserter(ret), toString);
        };
        convert(alternates);
        convert(ascii);
        return ret;
    };

    QList<UnicodeEmoticon> lstEmoticons;
    const QStringList keys = o.keys();
    for (const QString &key : keys) {
        UnicodeEmoticon emoticon;
        const QJsonObject emojiObj = o[key].toObject();
        emoticon.setKey(key);
        const QString unicodeStr = emojiObj["code_points"_L1].toObject()["fully_qualified"_L1].toString();
        Q_ASSERT(!unicodeStr.isEmpty());
        emoticon.setUnicode(unicodeStr);
        const QString category = emojiObj["category"_L1].toString();
        emoticon.setCategory(category);
        emoticon.setIdentifier(emojiObj["shortname"_L1].toString());
        emoticon.setOrder(emojiObj["order"_L1].toInt());
        emoticon.setDiversityChildren(!emojiObj["diversity_children"_L1].toArray().isEmpty());
        const auto shortnameAlternates = emojiObj["shortname_alternates"_L1].toArray();
        const auto ascii = emojiObj["ascii"_L1].toArray();
        emoticon.setAliases(aliases(shortnameAlternates, ascii));
        if (emoticon.isValid()) {
            lstEmoticons.append(std::move(emoticon));
        }
    }
    auto compareOrder = [](const UnicodeEmoticon &left, const UnicodeEmoticon &right) {
        return left.order() < right.order();
    };
    std::sort(lstEmoticons.begin(), lstEmoticons.end(), compareOrder);
    return lstEmoticons;
}

int UnicodeEmoticonParser::changeOrder(const QString &name)
{
    // ame "🚗"Category "travel", Name "🇿"Category "regional", Name "🏳️"Category "flags")
    if (name == "people"_L1) {
        return 1;
    } else if (name == "flags"_L1) {
        return 2;
    } else if (name == "travel"_L1) {
        return 3;
    } else if (name == "symbols"_L1) {
        return 4;
    } else if (name == "activity"_L1) {
        return 5;
    } else if (name == "objects"_L1) {
        return 6;
    } else if (name == "nature"_L1) {
        return 7;
    } else if (name == "food"_L1) {
        return 8;
    } else if (name == "regional"_L1) {
        return 9;
    } else {
        qCWarning(TEXTEMOTICONSCORE_LOG) << "Missing i18n translate " << name;
    }
    return 20;
}
