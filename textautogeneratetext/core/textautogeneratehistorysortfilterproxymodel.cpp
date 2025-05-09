/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratehistorysortfilterproxymodel.h"
#include "textautogeneratechatsmodel.h"

using namespace TextAutoGenerateText;
TextAutoGenerateHistorySortFilterProxyModel::TextAutoGenerateHistorySortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setSortRole(TextAutoGenerateChatsModel::DateTime);
    setFilterRole(TextAutoGenerateChatsModel::Title);
    sort(0);
    setRecursiveFilteringEnabled(true);
}

TextAutoGenerateHistorySortFilterProxyModel::~TextAutoGenerateHistorySortFilterProxyModel() = default;

bool TextAutoGenerateHistorySortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    // By default don't display any sections
    // Thanks to recursive filtering, the sections with channels will be displayed
    if (!source_parent.isValid()) {
        return false;
    }
    return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
}

bool TextAutoGenerateHistorySortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    if (!sourceModel()) {
        return false;
    }
    // assumes that we have a section → channels hierarchy
    if (left.parent().isValid() && right.parent().isValid()) {
        const qint64 leftDateTime = sourceModel()->data(left, TextAutoGenerateChatsModel::DateTime).toDouble();
        const qint64 rightDateTime = sourceModel()->data(right, TextAutoGenerateChatsModel::DateTime).toDouble();
        const bool leftFavorite = sourceModel()->data(left, TextAutoGenerateChatsModel::Favorite).toBool();
        const bool rightFavorite = sourceModel()->data(right, TextAutoGenerateChatsModel::Favorite).toBool();
        if (leftFavorite && (leftFavorite == rightFavorite)) {
            return leftDateTime < rightDateTime;
        }
        return leftDateTime < rightDateTime;
    }
    return left.row() < right.row();
}

#include "moc_textautogeneratehistorysortfilterproxymodel.cpp"
