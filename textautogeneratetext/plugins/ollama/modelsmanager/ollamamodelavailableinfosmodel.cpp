/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelavailableinfosmodel.h"

OllamaModelAvailableInfosModel::OllamaModelAvailableInfosModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

OllamaModelAvailableInfosModel::~OllamaModelAvailableInfosModel() = default;

int OllamaModelAvailableInfosModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mModelInfos.count();
}

QVariant OllamaModelAvailableInfosModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mModelInfos.count()) {
        return {};
    }
    const OllamaModelAvailableInfo &modelInfo = mModelInfos.at(index.row());
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
    }
    return {};
}

QList<OllamaModelAvailableInfo> OllamaModelAvailableInfosModel::modelInfos() const
{
    return mModelInfos;
}

void OllamaModelAvailableInfosModel::setModelInfos(const QList<OllamaModelAvailableInfo> &newModelInfos)
{
    beginResetModel();
    mModelInfos = newModelInfos;
    endResetModel();
}

#include "moc_ollamamodelavailableinfosmodel.cpp"
