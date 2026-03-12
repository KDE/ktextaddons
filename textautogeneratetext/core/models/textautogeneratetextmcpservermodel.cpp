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

TextAutoGenerateTextMcpServerModel::~TextAutoGenerateTextMcpServerModel()
{
    qDeleteAll(mMcpServers);
}

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
    const auto &instance = mMcpServers[id];
    switch (role) {
    case Qt::CheckStateRole:
    case MCPServerRoles::Enabled:
        instance->setEnabled(value.toBool());
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
    const auto &instance = mMcpServers[index.row()];
    switch (role) {
    case Qt::DisplayRole:
    case MCPServerRoles::Name:
        return instance->name();
    case Qt::CheckStateRole:
        return instance->enabled() ? Qt::Checked : Qt::Unchecked;
    case MCPServerRoles::Enabled:
        return instance->enabled();
    case MCPServerRoles::Identifier:
        return instance->identifier();
    default:
        break;
    }
    return {};
}

QList<TextAutoGenerateTextMcpServer *> TextAutoGenerateTextMcpServerModel::mcpServers() const
{
    return mMcpServers;
}

void TextAutoGenerateTextMcpServerModel::setMcpServers(const QList<TextAutoGenerateTextMcpServer *> &newTextInstances)
{
    beginResetModel();
    qDeleteAll(mMcpServers);
    mMcpServers.clear();
    mMcpServers = newTextInstances;
    endResetModel();
}

bool TextAutoGenerateTextMcpServerModel::isEmpty() const
{
    if (mMcpServers.isEmpty()) {
        return true;
    }
    for (const auto &inst : mMcpServers) {
        if (inst->enabled()) {
            return false;
        }
    }
    return true;
}

Qt::ItemFlags TextAutoGenerateTextMcpServerModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }

    return Qt::ItemIsUserCheckable | QAbstractListModel::flags(index);
}

#include "moc_textautogeneratetextmcpservermodel.cpp"
