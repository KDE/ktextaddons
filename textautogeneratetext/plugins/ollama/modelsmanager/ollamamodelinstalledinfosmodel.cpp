/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinstalledinfosmodel.h"

OllamaModelInstalledInfosModel::OllamaModelInstalledInfosModel(QObject *parent)
    : PluginCommonModelInstalledInfosModel{parent}
{
}

OllamaModelInstalledInfosModel::~OllamaModelInstalledInfosModel() = default;

QVariant OllamaModelInstalledInfosModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mModelInstalledInfos.count()) {
        return {};
    }

    auto parentResult = PluginCommonModelInstalledInfosModel::data(index, role);
    if (parentResult.isValid()) {
        return parentResult;
    }

    const OllamaModelInstalledInfo &modelInfo = mModelInstalledInfos.at(index.row());
    switch (role) {
    case ModelGeneratedName:
        return modelInfo.generateModelName();
    case Family:
        return modelInfo.family();
    case Languages:
        return modelInfo.languages();
    default:
        break;
    }
    return {};
}

#include "moc_ollamamodelinstalledinfosmodel.cpp"
