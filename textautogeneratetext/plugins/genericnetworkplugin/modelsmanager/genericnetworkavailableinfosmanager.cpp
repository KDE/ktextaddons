/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkavailableinfosmanager.h"

GenericNetworkAvailableInfosManager::GenericNetworkAvailableInfosManager(QObject *parent)
    : QObject{parent}
{
}

GenericNetworkAvailableInfosManager::~GenericNetworkAvailableInfosManager() = default;

#include "moc_genericnetworkavailableinfosmanager.cpp"
