/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelistviewdelegate.h"
#include "core/textautogeneratechatmodel.h"

using namespace TextAutogenerateText;
TextAutogenerateListViewDelegate::TextAutogenerateListViewDelegate(QObject *parent)
    : QStyledItemDelegate{parent}
{
}

TextAutogenerateListViewDelegate::~TextAutogenerateListViewDelegate() = default;

void TextAutogenerateListViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // TODO implement it
    QStyledItemDelegate::paint(painter, option, index);
}

QSize TextAutogenerateListViewDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // TODO implement it.
    return QStyledItemDelegate::sizeHint(option, index);
}

#include "moc_textautogeneratelistviewdelegate.cpp"
