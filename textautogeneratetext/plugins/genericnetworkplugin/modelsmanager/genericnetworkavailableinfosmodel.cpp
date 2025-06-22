/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkavailableinfosmodel.h"

GenericNetworkAvailableInfosModel::GenericNetworkAvailableInfosModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

GenericNetworkAvailableInfosModel::~GenericNetworkAvailableInfosModel() = default;

int GenericNetworkAvailableInfosModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mModelInfos.count();
}

QVariant GenericNetworkAvailableInfosModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mModelInfos.count()) {
        return {};
    }
    const GenericNetworkModelAvailableInfo &modelInfo = mModelInfos.at(index.row());
    /*
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
    */
    return {};
}

QList<GenericNetworkModelAvailableInfo> GenericNetworkAvailableInfosModel::modelInfos() const
{
    return mModelInfos;
}

void GenericNetworkAvailableInfosModel::setModelInfos(const QList<GenericNetworkModelAvailableInfo> &newModelInfos)
{
    beginResetModel();
    mModelInfos = newModelInfos;
    endResetModel();
}

#include "moc_genericnetworkavailableinfosmodel.cpp"
