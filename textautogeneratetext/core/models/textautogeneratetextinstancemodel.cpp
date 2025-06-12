/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancemodel.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextInstanceModel::TextAutoGenerateTextInstanceModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

TextAutoGenerateTextInstanceModel::~TextAutoGenerateTextInstanceModel() = default;

int TextAutoGenerateTextInstanceModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mTextInstances.count();
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
        return instance.name();
    case InstanceRoles::PluginName:
        return instance.pluginName();
    case InstanceRoles::Uuid:
        return instance.instanceUuid();
    case InstanceRoles::PluginIdentifer:
        return instance.pluginIdentifier();
    }
    return {};
}

QList<TextAutoGenerateTextInstance> TextAutoGenerateTextInstanceModel::textInstances() const
{
    return mTextInstances;
}

void TextAutoGenerateTextInstanceModel::setTextInstances(const QList<TextAutoGenerateTextInstance> &newTextInstances)
{
    beginResetModel();
    mTextInstances = newTextInstances;
    endResetModel();
}

void TextAutoGenerateTextInstanceModel::addTextInstances(const TextAutoGenerateTextInstance &instance)
{
    beginInsertRows(QModelIndex(), mTextInstances.count(), mTextInstances.count());
    mTextInstances.append(instance);
    endInsertRows();
}

void TextAutoGenerateTextInstanceModel::removeInstance(const QByteArray &uuid)
{
    auto matchesUuid = [&](const TextAutoGenerateTextInstance &instance) {
        return instance.instanceUuid() == uuid;
    };
    const auto answerIt = std::find_if(mTextInstances.begin(), mTextInstances.end(), matchesUuid);
    if (answerIt != mTextInstances.end()) {
        const int i = std::distance(mTextInstances.begin(), answerIt);
        beginRemoveRows(QModelIndex(), i, i);
        mTextInstances.removeAt(i);
        endRemoveRows();
    }
}

#include "moc_textautogeneratetextinstancemodel.cpp"
