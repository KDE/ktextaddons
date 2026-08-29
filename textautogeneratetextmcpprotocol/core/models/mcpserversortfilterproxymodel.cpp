/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserversortfilterproxymodel.h"
#include "mcpservermodel.h"

using namespace TextAutoGenerateTextMcpProtocolCore;
McpServerSortFilterProxyModel::McpServerSortFilterProxyModel(QObject *parent)
    : TextAddonsWidgets::SortFilterProxyModelBase{parent}
{
    setSortCaseSensitivity(Qt::CaseInsensitive);
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setFilterRole(McpServerModel::Name);
    sort(0);
}

McpServerSortFilterProxyModel::~McpServerSortFilterProxyModel() = default;

bool McpServerSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (mFilterString.trimmed().isEmpty()) {
        return true;
    }
    const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
    const QString serverName = sourceIndex.data(McpServerModel::Name).toString();
    if (const QString serverType = sourceIndex.data(McpServerModel::ServerType).toString(); contains(serverName) || contains(serverType)) {
        return true;
    }
    return false;
}

#include "moc_mcpserversortfilterproxymodel.cpp"
