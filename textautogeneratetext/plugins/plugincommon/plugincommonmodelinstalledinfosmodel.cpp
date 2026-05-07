/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "plugincommonmodelinstalledinfosmodel.h"

PluginCommonModelInstalledInfosModel::PluginCommonModelInstalledInfosModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

PluginCommonModelInstalledInfosModel::~PluginCommonModelInstalledInfosModel() = default;

#include "moc_plugincommonmodelinstalledinfosmodel.cpp"
