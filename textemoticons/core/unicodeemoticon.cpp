/*
   SPDX-FileCopyrightText: 2018-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "unicodeemoticon.h"
#include "emoticonunicodeutils.h"

using namespace TextEmoticonsCore;
UnicodeEmoticon::UnicodeEmoticon() = default;

bool UnicodeEmoticon::isValid() const
{
    return !mIdentifier.isEmpty() && !mUnicode.isEmpty();
}

QString UnicodeEmoticon::identifier() const
{
    return mIdentifier;
}

void UnicodeEmoticon::setIdentifier(const QString &name)
{
    mIdentifier = name;
}

QString UnicodeEmoticon::unicode() const
{
    return mUnicode;
}

QString UnicodeEmoticon::unicodeDisplay() const
{
    if (!mUnicode.isEmpty()) {
        if (mCachedHtml.isEmpty()) {
            mCachedHtml = QStringLiteral("<span style=\"font: x-large %3\" title=\"%2\">%1</span>")
                              .arg(mUnicode, mIdentifier, TextEmoticonsCore::EmoticonUnicodeUtils::emojiFontName());
        }
    }
    return mCachedHtml;
}

QString UnicodeEmoticon::key() const
{
    return mKey;
}

void UnicodeEmoticon::setKey(const QString &key)
{
    mKey = key;
}

bool UnicodeEmoticon::operator==(const UnicodeEmoticon &other) const
{
    return (mAliases == other.aliases()) && (mIdentifier == other.identifier()) && (mUnicode == other.unicode()) && (mCategory == other.category())
        && (mKey == other.key()) && (mOrder == other.order());
}

int UnicodeEmoticon::order() const
{
    return mOrder;
}

void UnicodeEmoticon::setOrder(int order)
{
    mOrder = order;
}

void UnicodeEmoticon::setUnicode(const QString &unicode)
{
    mUnicode = EmoticonUnicodeUtils::escapeUnicodeEmoji(unicode);
}

QString UnicodeEmoticon::category() const
{
    return mCategory;
}

void UnicodeEmoticon::setCategory(const QString &category)
{
    mCategory = category;
}

QStringList UnicodeEmoticon::aliases() const
{
    return mAliases;
}

void UnicodeEmoticon::setAliases(const QStringList &aliases)
{
    mAliases = aliases;
}

bool UnicodeEmoticon::hasEmoji(const QString &identifier) const
{
    return (mIdentifier == identifier) || (mUnicode == identifier) || mAliases.contains(identifier);
}

QDebug operator<<(QDebug d, const UnicodeEmoticon &t)
{
    d << "Identifier : " << t.identifier();
    d << "Unicode: " << t.unicode();
    d << "Category: " << t.category();
    d << "Aliases: " << t.aliases();
    d << "Order: " << t.order();
    d << "Key:" << t.key();
    return d;
}

#include "moc_unicodeemoticon.cpp"
