/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emoticonitemdelegate.h"
#include <textemoticonscore/emojimodel.h>
using namespace TextEmoticonsWidgets;
EmoticonItemDelegate::EmoticonItemDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{
}

EmoticonItemDelegate::~EmoticonItemDelegate() = default;

void TextEmoticonsWidgets::EmoticonItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const bool imageAnimated = index.data(TextEmoticonsCore::EmojiModel::Animated).toBool();
    if (imageAnimated) {
        // TODO implement it.
        QStyledItemDelegate::paint(painter, option, index);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}
