/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinfosmodel.h"

OllamaModelInfosModel::OllamaModelInfosModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

OllamaModelInfosModel::~OllamaModelInfosModel() = default;

int OllamaModelInfosModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mModelInfos.count();
}

QVariant OllamaModelInfosModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mModelInfos.count()) {
        return {};
    }
    const OllamaModelInfo &modelInfo = mModelInfos.at(index.row());
    switch (role) {
    case Categories:
        return QVariant::fromValue(modelInfo.categories());
    case Description:
        return modelInfo.description();
    case Author:
        return modelInfo.author();
    case Url:
        return modelInfo.url();
    case ModelName:
    case Qt::DisplayRole:
        return modelInfo.name();
    }
    return {};
}

QList<OllamaModelInfo> OllamaModelInfosModel::modelInfos() const
{
    return mModelInfos;
}

void OllamaModelInfosModel::setModelInfos(const QList<OllamaModelInfo> &newModelInfos)
{
    mModelInfos = newModelInfos;
}

#include "moc_ollamamodelinfosmodel.cpp"
