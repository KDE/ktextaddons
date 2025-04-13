/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelistviewdelegate.h"
#include "core/textautogeneratechatmodel.h"
#include <QPainter>

using namespace TextAutogenerateText;
TextAutogenerateListViewDelegate::TextAutogenerateListViewDelegate(QObject *parent)
    : QItemDelegate{parent}
{
}

TextAutogenerateListViewDelegate::~TextAutogenerateListViewDelegate() = default;

void TextAutogenerateListViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    drawBackground(painter, option, index);
    painter->restore();
    // TODO implement it
    QItemDelegate::paint(painter, option, index);
}

QSize TextAutogenerateListViewDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // TODO implement it.
    return QItemDelegate::sizeHint(option, index);
}

#include "moc_textautogeneratelistviewdelegate.cpp"
