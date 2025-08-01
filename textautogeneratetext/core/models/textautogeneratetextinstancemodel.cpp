/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancemodel.h"
#include "core/textautogeneratetextplugin.h"
#include "textautogeneratetextcore_debug.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextInstanceModel::TextAutoGenerateTextInstanceModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

TextAutoGenerateTextInstanceModel::~TextAutoGenerateTextInstanceModel()
{
    qDeleteAll(mTextInstances);
}

int TextAutoGenerateTextInstanceModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mTextInstances.count();
}

bool TextAutoGenerateTextInstanceModel::setData(const QModelIndex &idx, const QVariant &value, int role)
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

QVariant TextAutoGenerateTextInstanceModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mTextInstances.count()) {
        return {};
    }
    const auto &instance = mTextInstances[index.row()];
    switch (role) {
    case Qt::DisplayRole:
    case InstanceRoles::Name:
        return instance->displayName();
    case InstanceRoles::PluginName:
        return instance->pluginName();
    case InstanceRoles::Uuid:
        return instance->instanceUuid();
    case InstanceRoles::PluginIdentifier:
        return instance->pluginIdentifier();
    case InstanceRoles::Plugin:
        return QVariant::fromValue(instance->plugin());
    case Qt::CheckStateRole:
        return instance->enabled() ? Qt::Checked : Qt::Unchecked;
    case InstanceRoles::Enabled:
        return instance->enabled();
    case InstanceRoles::IsDefault:
        return !instance->instanceUuid().isEmpty() && !mCurrentinstance.isEmpty() && (instance->instanceUuid() == mCurrentinstance) && instance->enabled();
    case InstanceRoles::TranslatedPluginName:
        return instance->plugin()->translatedPluginName();
    default:
        break;
    }
    return {};
}

QList<TextAutoGenerateTextInstance *> TextAutoGenerateTextInstanceModel::textInstances() const
{
    return mTextInstances;
}

void TextAutoGenerateTextInstanceModel::setTextInstances(const QList<TextAutoGenerateTextInstance *> &newTextInstances)
{
    beginResetModel();
    qDeleteAll(mTextInstances);
    mTextInstances.clear();
    mTextInstances = newTextInstances;
    endResetModel();
}

bool TextAutoGenerateTextInstanceModel::isEmpty() const
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

QByteArray TextAutoGenerateTextInstanceModel::currentInstance() const
{
    return mCurrentinstance;
}

void TextAutoGenerateTextInstanceModel::setCurrentInstance(const QByteArray &newCurrentinstance)
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

TextAutoGenerateTextPlugin *TextAutoGenerateTextInstanceModel::currentPlugin() const
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
        return instance->instanceUuid() == mCurrentinstance;
    };
    const auto answerIt = std::find_if(mTextInstances.constBegin(), mTextInstances.constEnd(), matchesUuid);
    if (answerIt != mTextInstances.constEnd()) {
        return (*answerIt)->plugin();
    }
    return mTextInstances.constFirst()->plugin();
}

void TextAutoGenerateTextInstanceModel::addInstance(TextAutoGenerateTextInstance *instance)
{
    beginInsertRows(QModelIndex(), mTextInstances.count(), mTextInstances.count());
    mTextInstances.append(instance);
    endInsertRows();
}

TextAutoGenerateTextPlugin *TextAutoGenerateTextInstanceModel::removeInstance(const QByteArray &uuid)
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

TextAutoGenerateTextPlugin *TextAutoGenerateTextInstanceModel::editInstance(const QByteArray &uuid)
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

Qt::ItemFlags TextAutoGenerateTextInstanceModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }

    return Qt::ItemIsUserCheckable | QAbstractListModel::flags(index);
}

#include "moc_textautogeneratetextinstancemodel.cpp"
