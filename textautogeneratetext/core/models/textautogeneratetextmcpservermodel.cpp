/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextmcpservermodel.h"
#include "core/textautogeneratetextplugin.h"
#include "textautogeneratetextcore_debug.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextMcpServerModel::TextAutoGenerateTextMcpServerModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

TextAutoGenerateTextMcpServerModel::~TextAutoGenerateTextMcpServerModel() = default;

int TextAutoGenerateTextMcpServerModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mMcpServers.count();
}

bool TextAutoGenerateTextMcpServerModel::setData(const QModelIndex &idx, const QVariant &value, int role)
{
    if (!idx.isValid()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "ERROR: invalid index";
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

QVariant TextAutoGenerateTextMcpServerModel::data(const QModelIndex &index, int role) const
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

QList<TextAutoGenerateTextMcpServer> TextAutoGenerateTextMcpServerModel::mcpServers() const
{
    return mMcpServers;
}

void TextAutoGenerateTextMcpServerModel::addMcpServer(const TextAutoGenerateTextMcpServer &server)
{
    beginInsertRows(QModelIndex(), mMcpServers.count(), mMcpServers.count());
    mMcpServers.append(server);
    endInsertRows();
}

void TextAutoGenerateTextMcpServerModel::setMcpServers(const QList<TextAutoGenerateTextMcpServer> &newTextInstances)
{
    beginResetModel();
    mMcpServers = newTextInstances;
    endResetModel();
}
TextAutoGenerateTextMcpServer TextAutoGenerateTextMcpServerModel::mpcServer(const QByteArray &identifier) const
{
    if (identifier.isEmpty()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Empty identifier it's a bug";
        return {};
    }
    const auto matchesIdentifier = [&](const TextAutoGenerateTextMcpServer &msg) {
        return msg.identifier() == identifier;
    };
    const auto it = std::find_if(mMcpServers.begin(), mMcpServers.end(), matchesIdentifier);
    if (it != mMcpServers.end()) {
        return *it;
    }
    return {};
}

bool TextAutoGenerateTextMcpServerModel::isEmpty() const
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

void TextAutoGenerateTextMcpServerModel::removeMcpServer(const QByteArray &identifier)
{
    if (identifier.isEmpty()) {
        return;
    }
    const auto matchesIdentifier = [&](const TextAutoGenerateTextMcpServer &msg) {
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

Qt::ItemFlags TextAutoGenerateTextMcpServerModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }

    return Qt::ItemIsUserCheckable | QAbstractListModel::flags(index);
}

#include "moc_textautogeneratetextmcpservermodel.cpp"
