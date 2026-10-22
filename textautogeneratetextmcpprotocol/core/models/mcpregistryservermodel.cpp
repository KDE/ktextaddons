/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpregistryservermodel.h"

using namespace TextAutoGenerateTextMcpProtocolCore;
McpRegistryServerModel::McpRegistryServerModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

McpRegistryServerModel::~McpRegistryServerModel() = default;

int McpRegistryServerModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return mServers.count();
}

QVariant McpRegistryServerModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mServers.count()) {
        return {};
    }
    const McpRegistryServerInfo &info = mServers.at(index.row());
    switch (role) {
    case Qt::DisplayRole:
        return info.displayName();
    case Qt::ToolTipRole:
    case McpRegistryServerRoles::Name:
        return info.name();
    case McpRegistryServerRoles::Description:
        return info.description();
    case McpRegistryServerRoles::Version:
        return info.version();
    }
    return {};
}

void McpRegistryServerModel::setServers(const QList<McpRegistryServerInfo> &servers)
{
    beginResetModel();
    mServers = servers;
    endResetModel();
}

void McpRegistryServerModel::appendServers(const QList<McpRegistryServerInfo> &servers)
{
    if (servers.isEmpty()) {
        return;
    }
    beginInsertRows({}, mServers.count(), mServers.count() + servers.count() - 1);
    mServers.append(servers);
    endInsertRows();
}

void McpRegistryServerModel::clear()
{
    if (mServers.isEmpty()) {
        return;
    }
    beginResetModel();
    mServers.clear();
    endResetModel();
}

McpRegistryServerInfo McpRegistryServerModel::serverInfo(int row) const
{
    if (row < 0 || row >= mServers.count()) {
        return {};
    }
    return mServers.at(row);
}

#include "moc_mcpregistryservermodel.cpp"
