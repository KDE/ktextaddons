/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratehistorysortfilterproxymodel.h"
#include "textautogeneratechatmodel.h"
#include "textautogeneratemessage.h"

using namespace TextAutogenerateText;
TextAutoGenerateHistorySortFilterProxyModel::TextAutoGenerateHistorySortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setSortRole(TextAutoGenerateChatModel::DateTimeRole);
    setFilterRole(TextAutoGenerateChatModel::MessageRole);
    sort(0);
}

TextAutoGenerateHistorySortFilterProxyModel::~TextAutoGenerateHistorySortFilterProxyModel() = default;

bool TextAutoGenerateHistorySortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    // TODO add headers
    return true;
}

bool TextAutoGenerateHistorySortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    const TextAutoGenerateMessage::Sender sender =
        sourceModel()->index(source_row, 0).data(TextAutoGenerateChatModel::SenderRole).value<TextAutoGenerateMessage::Sender>();
    if (sender != TextAutoGenerateMessage::Sender::User) {
        return false;
    }
    return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
}

#include "moc_textautogeneratehistorysortfilterproxymodel.cpp"
