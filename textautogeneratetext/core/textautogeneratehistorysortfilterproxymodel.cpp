/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratehistorysortfilterproxymodel.h"
#include "textautogeneratehistorymodel.h"

using namespace TextAutogenerateText;
TextAutoGenerateHistorySortFilterProxyModel::TextAutoGenerateHistorySortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setFilterRole(TextAutoGenerateHistoryModel::DateTime);
    sort(0);
}

TextAutoGenerateHistorySortFilterProxyModel::~TextAutoGenerateHistorySortFilterProxyModel() = default;

bool TextAutoGenerateHistorySortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    // TODO implement filter subject
    return true;
}

bool TextAutoGenerateHistorySortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    // TODO
    return true;
}

#include "moc_textautogeneratehistorysortfilterproxymodel.cpp"
