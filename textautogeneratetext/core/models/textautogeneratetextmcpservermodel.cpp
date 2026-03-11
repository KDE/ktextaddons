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
    qDeleteAll(mTextInstances);
}

int TextAutoGenerateTextMcpServerModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mTextInstances.count();
}

bool TextAutoGenerateTextMcpServerModel::setData(const QModelIndex &idx, const QVariant &value, int role)
{
    if (!idx.isValid()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "ERROR: invalid index";
        return false;
    }
    const int id = idx.row();
    const auto &instance = mTextInstances[id];
    switch (role) {
    case Qt::CheckStateRole:
    case InstanceRoles::Enabled:
        instance->setEnabled(value.toBool());
        Q_EMIT dataChanged(idx, idx, {InstanceRoles::Enabled});
        return true;
    default:
        break;
    }
    return QAbstractListModel::setData(idx, value, role);
}

QVariant TextAutoGenerateTextMcpServerModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mTextInstances.count()) {
        return {};
    }
    const auto &instance = mTextInstances[index.row()];
    switch (role) {
    case Qt::DisplayRole:
    case InstanceRoles::Name:
        return instance->displayName();
    case Qt::CheckStateRole:
        return instance->enabled() ? Qt::Checked : Qt::Unchecked;
    case InstanceRoles::Enabled:
        return instance->enabled();
    default:
        break;
    }
    return {};
}

QStringList TextAutoGenerateTextMcpServerModel::instanceDisplayNames() const
{
    QStringList lstDisplayNames;
    lstDisplayNames.reserve(mTextInstances.size());
    for (const auto &inst : mTextInstances) {
        lstDisplayNames.append(inst->displayName());
    }
    return lstDisplayNames;
}

QList<TextAutoGenerateTextInstance *> TextAutoGenerateTextMcpServerModel::textInstances() const
{
    return mTextInstances;
}

void TextAutoGenerateTextMcpServerModel::setTextInstances(const QList<TextAutoGenerateTextInstance *> &newTextInstances)
{
    beginResetModel();
    qDeleteAll(mTextInstances);
    mTextInstances.clear();
    mTextInstances = newTextInstances;
    endResetModel();
}

bool TextAutoGenerateTextMcpServerModel::isEmpty() const
{
    if (mTextInstances.isEmpty()) {
        return true;
    }
    for (const auto &inst : mTextInstances) {
        if (inst->enabled()) {
            return false;
        }
    }
    return true;
}

QByteArray TextAutoGenerateTextMcpServerModel::currentInstance() const
{
    return mCurrentinstance;
}

void TextAutoGenerateTextMcpServerModel::setCurrentInstance(const QByteArray &newCurrentinstance)
{
    if (mCurrentinstance != newCurrentinstance) {
        auto matchesUuid = [&](TextAutoGenerateTextInstance *instance) {
            return instance->instanceUuid() == newCurrentinstance;
        };
        const auto answerIt = std::find_if(mTextInstances.constBegin(), mTextInstances.constEnd(), matchesUuid);
        if (answerIt == mTextInstances.constEnd()) {
            // If we don't find it. => clear it.
            mCurrentinstance.clear();
            return;
        }
        beginResetModel();
        mCurrentinstance = newCurrentinstance;
        endResetModel();
    }
}

TextAutoGenerateTextPlugin *TextAutoGenerateTextMcpServerModel::currentPlugin() const
{
    if (isEmpty()) {
        return nullptr;
    }
    if (mCurrentinstance.isEmpty()) {
        // Fall back to first enable instance
        for (const auto &inst : mTextInstances) {
            if (inst->enabled()) {
                return inst->plugin();
            }
        }
        return nullptr;
    }
    auto matchesUuid = [&](TextAutoGenerateTextInstance *instance) {
        return (instance->instanceUuid() == mCurrentinstance) && instance->enabled();
    };
    const auto answerIt = std::find_if(mTextInstances.constBegin(), mTextInstances.constEnd(), matchesUuid);
    if (answerIt != mTextInstances.constEnd()) {
        return (*answerIt)->plugin();
    }
    // Fall back to first enable instance
    for (const auto &inst : mTextInstances) {
        if (inst->enabled()) {
            return inst->plugin();
        }
    }
    return nullptr;
}

void TextAutoGenerateTextMcpServerModel::addInstance(TextAutoGenerateTextInstance *instance)
{
    beginInsertRows(QModelIndex(), mTextInstances.count(), mTextInstances.count());
    mTextInstances.append(instance);
    endInsertRows();
}

TextAutoGenerateTextPlugin *TextAutoGenerateTextMcpServerModel::removeInstance(const QByteArray &uuid)
{
    auto matchesUuid = [&](TextAutoGenerateTextInstance *instance) {
        return instance->instanceUuid() == uuid;
    };
    TextAutoGenerateTextPlugin *plugin = nullptr;
    const auto answerIt = std::find_if(mTextInstances.constBegin(), mTextInstances.constEnd(), matchesUuid);
    if (answerIt != mTextInstances.constEnd()) {
        const int i = std::distance(mTextInstances.constBegin(), answerIt);
        beginRemoveRows(QModelIndex(), i, i);
        plugin = mTextInstances.at(i)->plugin();
        mTextInstances.removeAt(i);
        endRemoveRows();
    }
    return plugin;
}

TextAutoGenerateTextPlugin *TextAutoGenerateTextMcpServerModel::editInstance(const QByteArray &uuid)
{
    auto matchesUuid = [&](TextAutoGenerateTextInstance *instance) {
        return instance->instanceUuid() == uuid;
    };
    const auto answerIt = std::find_if(mTextInstances.constBegin(), mTextInstances.constEnd(), matchesUuid);
    if (answerIt != mTextInstances.constEnd()) {
        const int i = std::distance(mTextInstances.constBegin(), answerIt);
        return mTextInstances.at(i)->plugin();
    }
    qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Instance not found for uuid:" << uuid;
    return nullptr;
}

Qt::ItemFlags TextAutoGenerateTextMcpServerModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }

    return Qt::ItemIsUserCheckable | QAbstractListModel::flags(index);
}

#include "moc_textautogeneratetextmcpservermodel.cpp"
