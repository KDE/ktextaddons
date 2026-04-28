/*
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "lmstudiomodelinstalledinfosmodel.h"
#include "modelsmanager/lmstudiomodelinstalledinfo.h"

LMStudioModelInstalledInfosModel::LMStudioModelInstalledInfosModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

LMStudioModelInstalledInfosModel::~LMStudioModelInstalledInfosModel() = default;

int LMStudioModelInstalledInfosModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mModelInstalledInfos.count();
}

QVariant LMStudioModelInstalledInfosModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mModelInstalledInfos.count()) {
        return {};
    }
    const LMStudioModelInstalledInfo &modelInfo = mModelInstalledInfos.at(index.row());
    switch (role) {
    case DescriptionInfo:
        return QVariant::fromValue(modelInfo);
    case QuantizationLevel:
        return modelInfo.quantizationLevel();
    case ParameterSize:
        return modelInfo.parameterSize();
    case OriginalName:
        return modelInfo.model();
    case Name:
    case Qt::DisplayRole:
        return modelInfo.name();
    case Categories:
        return QVariant::fromValue(modelInfo.categories());
    default:
        break;
    }
    return {};
}

QList<LMStudioModelInstalledInfo> LMStudioModelInstalledInfosModel::modelInstalledInfos() const
{
    return mModelInstalledInfos;
}

void LMStudioModelInstalledInfosModel::setModelInstalledInfos(const QList<LMStudioModelInstalledInfo> &newModelInfos)
{
    beginResetModel();
    mModelInstalledInfos = newModelInfos;
    endResetModel();
}

#include "moc_lmstudiomodelinstalledinfosmodel.cpp"
