/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinstalledinfosmodel.h"

OllamaModelInstalledInfosModel::OllamaModelInstalledInfosModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

OllamaModelInstalledInfosModel::~OllamaModelInstalledInfosModel() = default;

int OllamaModelInstalledInfosModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mModelInstalledInfos.count();
}

QVariant OllamaModelInstalledInfosModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mModelInstalledInfos.count()) {
        return {};
    }
    const OllamaModelInstalledInfo &modelInfo = mModelInstalledInfos.at(index.row());
    switch (role) {
    case Family:
        return modelInfo.family();
    case QuantizationLevel:
        return modelInfo.quantizationLevel();
    case ParameterSize:
        return modelInfo.parameterSize();
    case ModelName:
    case Qt::DisplayRole:
        return modelInfo.name();
    }
    return {};
}

QList<OllamaModelInstalledInfo> OllamaModelInstalledInfosModel::modelInstalledInfos() const
{
    return mModelInstalledInfos;
}

void OllamaModelInstalledInfosModel::setModelInstalledInfos(const QList<OllamaModelInstalledInfo> &newModelInfos)
{
    mModelInstalledInfos = newModelInfos;
}

#include "moc_ollamamodelinstalledinfosmodel.cpp"
