/*
   SPDX-FileCopyrightText: 2021-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emojimodel.h"
using namespace TextEmoticonsCore;
EmojiModel::EmojiModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

EmojiModel::~EmojiModel() = default;

int EmojiModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mEmoticonList.count();
}

QVariant EmojiModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mEmoticonList.count()) {
        return {};
    }

    const auto &unicodeEmoti = mEmoticonList.at(index.row());
    switch (role) {
    case Qt::DisplayRole:
    case UnicodeEmoji:
        return unicodeEmoti.unicode();
    case Category:
        return unicodeEmoti.category();
    case Order:
        return unicodeEmoti.order();
    case Identifier:
    case Qt::ToolTipRole:
        return unicodeEmoti.identifier();
    }
    return {};
}

const QList<TextEmoticonsCore::UnicodeEmoticon> &EmojiModel::emoticonList() const
{
    return mEmoticonList;
}

void EmojiModel::setEmoticonList(const QList<TextEmoticonsCore::UnicodeEmoticon> &newEmoticonList)
{
    beginResetModel();
    mEmoticonList = newEmoticonList;
    endResetModel();
}

QList<TextEmoticonsCore::CustomEmoji> EmojiModel::customEmojiList() const
{
    return mCustomEmojiList;
}

void EmojiModel::setCustomEmojiList(const QList<TextEmoticonsCore::CustomEmoji> &newCustomEmojiList)
{
    mCustomEmojiList = newCustomEmojiList;
}

TextEmoticonsCore::CustomEmojiIconManager *EmojiModel::customEmojiIconManager() const
{
    return mCustomEmojiIconManager;
}

void EmojiModel::setCustomEmojiIconManager(TextEmoticonsCore::CustomEmojiIconManager *newCustomEmojiIconManager)
{
    mCustomEmojiIconManager = newCustomEmojiIconManager;
}
