/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserversortfilterproxymodel.h"
#include "mcpservermodel.h"

using namespace TextAutoGenerateText;
McpServerSortFilterProxyModel::McpServerSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    setSortCaseSensitivity(Qt::CaseInsensitive);
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setFilterRole(TextAutoGenerateTextMcpServerModel::Name);
    sort(0);
}

McpServerSortFilterProxyModel::~McpServerSortFilterProxyModel() = default;

bool McpServerSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (mSearchText.trimmed().isEmpty()) {
        return true;
    }
    const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
    const QString serverName = sourceIndex.data(TextAutoGenerateTextMcpServerModel::Name).toString();
    if (serverName.contains(mSearchText, Qt::CaseInsensitive)) {
        return true;
    }
    return false;
}

QString McpServerSortFilterProxyModel::searchText() const
{
    return mSearchText;
}

void McpServerSortFilterProxyModel::setSearchText(const QString &newSearchText)
{
    if (mSearchText != newSearchText) {
#if QT_VERSION >= QT_VERSION_CHECK(6, 10, 0)
        beginFilterChange();
#endif
        mSearchText = newSearchText;
#if QT_VERSION >= QT_VERSION_CHECK(6, 10, 0)
        endFilterChange(QSortFilterProxyModel::Direction::Rows);
#else
        invalidateFilter();
#endif
    }
}

#include "moc_mcpserversortfilterproxymodel.cpp"
