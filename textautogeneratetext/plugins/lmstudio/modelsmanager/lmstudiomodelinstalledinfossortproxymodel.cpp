/*
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "lmstudiomodelinstalledinfossortproxymodel.h"
#include "lmstudiomodelinstalledinfosmodel.h"

LMStudioModelInstalledInfosSortProxyModel::LMStudioModelInstalledInfosSortProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setSortCaseSensitivity(Qt::CaseInsensitive);
    setFilterRole(LMStudioModelInstalledInfosModel::OriginalName);
    setSortRole(LMStudioModelInstalledInfosModel::OriginalName);
}

LMStudioModelInstalledInfosSortProxyModel::~LMStudioModelInstalledInfosSortProxyModel() = default;

#include "moc_lmstudiomodelinstalledinfossortproxymodel.cpp"
