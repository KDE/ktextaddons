/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkmodelavailableinfossortproxymodel.h"

GenericNetworkModelAvailableInfosSortProxyModel::GenericNetworkModelAvailableInfosSortProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
}

GenericNetworkModelAvailableInfosSortProxyModel::~GenericNetworkModelAvailableInfosSortProxyModel() = default;
