/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkmodelavailableinfossortproxymodel.h"
#include "genericnetworkavailableinfosmodel.h"

GenericNetworkModelAvailableInfosSortProxyModel::GenericNetworkModelAvailableInfosSortProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setSortCaseSensitivity(Qt::CaseInsensitive);
    setFilterRole(GenericNetworkAvailableInfosModel::Identifier);
    setSortRole(GenericNetworkAvailableInfosModel::Identifier);
}

GenericNetworkModelAvailableInfosSortProxyModel::~GenericNetworkModelAvailableInfosSortProxyModel() = default;

#include "moc_genericnetworkmodelavailableinfossortproxymodel.cpp"
