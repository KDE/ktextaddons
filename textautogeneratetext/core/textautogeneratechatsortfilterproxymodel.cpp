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
    setFilterRole(TextAutoGenerateChatModel::DateTimeRole);
}

TextAutoGenerateChatSortFilterProxyModel::~TextAutoGenerateChatSortFilterProxyModel() = default;

bool TextAutoGenerateChatSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    switch (mMessageType) {
    case MessageType::Unknown:
    case MessageType::All:
        return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
    case MessageType::Archived: {
        const bool archived = sourceModel()->index(source_row, 0).data(TextAutoGenerateChatModel::ArchivedRole).toBool();
        return archived;
    }
    case MessageType::Active: {
        const bool archived = sourceModel()->index(source_row, 0).data(TextAutoGenerateChatModel::ArchivedRole).toBool();
        return !archived;
    }
    }
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
