/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "lmstudiomodelinstalledinfosmodel.h"
#include "plugincommonmodelinstalledinfosmodel.h"

LMStudioModelInstalledInfosModel::LMStudioModelInstalledInfosModel(QObject *parent)
    : PluginCommonModelInstalledInfosModel{parent}
{
}

LMStudioModelInstalledInfosModel::~LMStudioModelInstalledInfosModel() = default;

QVariant LMStudioModelInstalledInfosModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mModelInstalledInfos.count()) {
        return {};
    }

    auto parentResult = PluginCommonModelInstalledInfosModel::data(index, role);
    if (parentResult.isValid()) {
        return parentResult;
    }

    const LMStudioModelInstalledInfo &modelInfo = mModelInstalledInfos.at(index.row());
    switch (role) {
    case Publisher:
        return modelInfo.publisher();
    default:
        break;
    }
    return {};
}

#include "moc_lmstudiomodelinstalledinfosmodel.cpp"
