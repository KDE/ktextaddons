/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpservermodel.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"

using namespace TextAutoGenerateTextMcpProtocolCore;
McpServerModel::McpServerModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

McpServerModel::~McpServerModel() = default;

int McpServerModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mMcpServers.count();
}

bool McpServerModel::setData(const QModelIndex &idx, const QVariant &value, int role)
{
    if (!idx.isValid()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "ERROR: invalid index";
        return false;
    }
    const int id = idx.row();
    auto &server = mMcpServers[id];
    switch (role) {
    case Qt::CheckStateRole:
    case MCPServerRoles::Enabled:
        server.setEnabled(value.toBool());
        Q_EMIT dataChanged(idx, idx, {MCPServerRoles::Enabled});
        return true;
    default:
        break;
    }
    return QAbstractListModel::setData(idx, value, role);
}

QVariant McpServerModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mMcpServers.count()) {
        return {};
    }
    const auto &server = mMcpServers[index.row()];
    switch (role) {
    case Qt::DisplayRole:
    case MCPServerRoles::Name:
        return server.name();
    case Qt::CheckStateRole:
        return server.enabled() ? Qt::Checked : Qt::Unchecked;
    case MCPServerRoles::Enabled:
        return server.enabled();
    case MCPServerRoles::Identifier:
        return server.identifier();
    default:
        break;
    }
    return {};
}

QList<McpServer> McpServerModel::mcpServers() const
{
    return mMcpServers;
}

void McpServerModel::addMcpServer(const McpServer &server)
{
    beginInsertRows(QModelIndex(), mMcpServers.count(), mMcpServers.count());
    mMcpServers.append(server);
    endInsertRows();
}

void McpServerModel::setMcpServers(const QList<McpServer> &newTextInstances)
{
    beginResetModel();
    mMcpServers = newTextInstances;
    endResetModel();
}

McpServer McpServerModel::mpcServer(const QByteArray &identifier) const
{
    if (identifier.isEmpty()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Empty identifier it's a bug";
        return {};
    }
    const auto matchesIdentifier = [&](const McpServer &msg) {
        return msg.identifier() == identifier;
    };
    const auto it = std::find_if(mMcpServers.begin(), mMcpServers.end(), matchesIdentifier);
    if (it != mMcpServers.end()) {
        return *it;
    }
    return {};
}

bool McpServerModel::isEmpty() const
{
    if (mMcpServers.isEmpty()) {
        return true;
    }
    for (const auto &server : mMcpServers) {
        if (server.enabled()) {
            return false;
        }
    }
    return true;
}

void McpServerModel::removeMcpServer(const QByteArray &identifier)
{
    if (identifier.isEmpty()) {
        return;
    }
    const auto matchesIdentifier = [&](const McpServer &msg) {
        return msg.identifier() == identifier;
    };
    const auto it = std::find_if(mMcpServers.begin(), mMcpServers.end(), matchesIdentifier);
    if (it != mMcpServers.end()) {
        const int i = std::distance(mMcpServers.begin(), it);
        beginRemoveRows(QModelIndex(), i, i);
        mMcpServers.removeAt(i);
        endRemoveRows();
    }
}

Qt::ItemFlags McpServerModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }

    return Qt::ItemIsUserCheckable | QAbstractListModel::flags(index);
}

#include "moc_mcpservermodel.cpp"
