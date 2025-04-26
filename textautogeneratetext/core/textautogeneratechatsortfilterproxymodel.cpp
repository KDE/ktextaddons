/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratechatsortfilterproxymodel.h"
#include "textautogeneratechatmodel.h"

using namespace TextAutogenerateText;
TextAutoGenerateChatSortFilterProxyModel::TextAutoGenerateChatSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
}

TextAutoGenerateChatSortFilterProxyModel::~TextAutoGenerateChatSortFilterProxyModel() = default;

bool TextAutoGenerateChatSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    // TODO implement it
    return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
}

TextAutoGenerateChatSortFilterProxyModel::MessageType TextAutoGenerateChatSortFilterProxyModel::messageType() const
{
    return mMessageType;
}

void TextAutoGenerateChatSortFilterProxyModel::setMessageType(MessageType newMessageType)
{
    if (mMessageType != newMessageType) {
        mMessageType = newMessageType;
        invalidateFilter();
    }
}

#include "moc_textautogeneratechatsortfilterproxymodel.cpp"
