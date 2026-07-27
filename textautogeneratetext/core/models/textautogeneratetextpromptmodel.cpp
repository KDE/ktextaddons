/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextpromptmodel.h"
#include "core/textautogeneratetextplugin.h"
#include "textautogeneratetextcore_debug.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextPromptModel::TextAutoGenerateTextPromptModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

TextAutoGenerateTextPromptModel::~TextAutoGenerateTextPromptModel()
{
    qDeleteAll(mTextInstances);
}

int TextAutoGenerateTextPromptModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mTextInstances.count();
}

bool TextAutoGenerateTextPromptModel::setData(const QModelIndex &idx, const QVariant &value, int role)
{
    if (!idx.isValid() || idx.row() < 0 || idx.row() >= mTextInstances.count()) {
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

QVariant TextAutoGenerateTextPromptModel::data(const QModelIndex &index, int role) const
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

QStringList TextAutoGenerateTextPromptModel::instanceDisplayNames() const
{
    QStringList lstDisplayNames;
    lstDisplayNames.reserve(mTextInstances.size());
    for (const auto &inst : mTextInstances) {
        lstDisplayNames.append(inst->displayName());
    }
    return lstDisplayNames;
}

QList<TextAutoGenerateTextInstance *> TextAutoGenerateTextPromptModel::textInstances() const
{
    return mTextInstances;
}

void TextAutoGenerateTextPromptModel::setTextInstances(const QList<TextAutoGenerateTextInstance *> &newTextInstances)
{
    beginResetModel();
    qDeleteAll(mTextInstances);
    mTextInstances.clear();
    mTextInstances = newTextInstances;
    endResetModel();
}

bool TextAutoGenerateTextPromptModel::isEmpty() const
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

QByteArray TextAutoGenerateTextPromptModel::currentInstance() const
{
    return mCurrentinstance;
}

void TextAutoGenerateTextPromptModel::setCurrentInstance(const QByteArray &newCurrentinstance)
{
    if (mCurrentinstance != newCurrentinstance) {
        auto matchesUuid = [&](TextAutoGenerateTextInstance *instance) {
            return instance->instanceUuid() == newCurrentinstance;
        };
        const auto answerIt = std::find_if(mTextInstances.constBegin(), mTextInstances.constEnd(), matchesUuid);

        // Notify for old current instance row before changing state
        auto notifyRow = [&](const QByteArray &uuid) {
            auto it = std::find_if(mTextInstances.constBegin(), mTextInstances.constEnd(), [&](TextAutoGenerateTextInstance *instance) {
                return instance->instanceUuid() == uuid;
            });
            if (it != mTextInstances.constEnd()) {
                const int row = std::distance(mTextInstances.constBegin(), it);
                const auto idx = index(row, 0);
                Q_EMIT dataChanged(idx, idx, {InstanceRoles::IsDefault});
            }
        };

        if (answerIt == mTextInstances.constEnd()) {
            // If we don't find it. => clear it.
            const QByteArray oldInstance = mCurrentinstance;
            mCurrentinstance.clear();
            notifyRow(oldInstance);
            return;
        }
        notifyRow(mCurrentinstance);
        mCurrentinstance = newCurrentinstance;
        const int newRow = std::distance(mTextInstances.constBegin(), answerIt);
        const auto newIdx = index(newRow, 0);
        Q_EMIT dataChanged(newIdx, newIdx, {InstanceRoles::IsDefault});
    }
}

TextAutoGenerateTextPlugin *TextAutoGenerateTextPromptModel::currentPlugin() const
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

void TextAutoGenerateTextPromptModel::addInstance(TextAutoGenerateTextInstance *instance)
{
    beginInsertRows(QModelIndex(), mTextInstances.count(), mTextInstances.count());
    mTextInstances.append(instance);
    endInsertRows();
}

void TextAutoGenerateTextPromptModel::removeInstance(const QByteArray &uuid)
{
    auto matchesUuid = [&](TextAutoGenerateTextInstance *instance) {
        return instance->instanceUuid() == uuid;
    };
    const auto answerIt = std::find_if(mTextInstances.constBegin(), mTextInstances.constEnd(), matchesUuid);
    if (answerIt != mTextInstances.constEnd()) {
        const int i = std::distance(mTextInstances.constBegin(), answerIt);
        beginRemoveRows(QModelIndex(), i, i);
        auto instance = mTextInstances.at(i);
        mTextInstances.removeAt(i);
        endRemoveRows();
        if (auto plugin = instance->plugin()) {
            plugin->remove();
        }
        delete instance;
    }
}

TextAutoGenerateTextPlugin *TextAutoGenerateTextPromptModel::editInstance(const QByteArray &uuid)
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

Qt::ItemFlags TextAutoGenerateTextPromptModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }

    return Qt::ItemIsUserCheckable | QAbstractListModel::flags(index);
}

#include "moc_textautogeneratetextpromptmodel.cpp"
