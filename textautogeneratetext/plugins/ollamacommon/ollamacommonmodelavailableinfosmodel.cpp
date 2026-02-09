/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamacommonmodelavailableinfosmodel.h"

OllamaCommonModelAvailableInfosModel::OllamaCommonModelAvailableInfosModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

OllamaCommonModelAvailableInfosModel::~OllamaCommonModelAvailableInfosModel() = default;

int OllamaCommonModelAvailableInfosModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mModelInfos.count();
}

QVariant OllamaCommonModelAvailableInfosModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mModelInfos.count()) {
        return {};
    }
    const OllamaCommonModelAvailableInfo &modelInfo = mModelInfos.at(index.row());
    switch (role) {
    case CategoriesName:
        return modelInfo.categoriesName();
    case Categories:
        return QVariant::fromValue(modelInfo.categories());
    case Description:
        return modelInfo.description();
    case Author:
        return modelInfo.author();
    case Url:
        return modelInfo.url();
    case Languages:
        return modelInfo.languages();
    case Tags:
        return QVariant::fromValue(modelInfo.tags());
    case ModelName:
    case Qt::DisplayRole:
        return modelInfo.name();
    default:
        break;
    }
    return {};
}

QList<OllamaCommonModelAvailableInfo> OllamaCommonModelAvailableInfosModel::modelInfos() const
{
    return mModelInfos;
}

void OllamaCommonModelAvailableInfosModel::setModelInfos(const QList<OllamaCommonModelAvailableInfo> &newModelInfos)
{
    beginResetModel();
    mModelInfos = newModelInfos;
    endResetModel();
}

#include "moc_ollamacommonmodelavailableinfosmodel.cpp"
