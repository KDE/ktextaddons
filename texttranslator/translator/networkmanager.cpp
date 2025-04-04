/*
  SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "networkmanager.h"
#include "texttranslator_debug.h"
#include <QNetworkInformation>
using namespace TextTranslator;

Q_GLOBAL_STATIC(NetworkManager, s_pNetworkManagerSelf)

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent)
{
    QNetworkInformation::instance()->loadBackendByFeatures(QNetworkInformation::Feature::Reachability);
    connect(QNetworkInformation::instance(), &QNetworkInformation::reachabilityChanged, this, [this](QNetworkInformation::Reachability newReachability) {
        Q_EMIT networkStatusChanged(newReachability == QNetworkInformation::Reachability::Online);
    });
}

NetworkManager::~NetworkManager() = default;

NetworkManager *NetworkManager::self()
{
    return s_pNetworkManagerSelf();
}

bool NetworkManager::isOnline() const
{
    if (QNetworkInformation::loadBackendByFeatures(QNetworkInformation::Feature::Reachability)) {
        return QNetworkInformation::instance()->reachability() == QNetworkInformation::Reachability::Online;
    } else {
        qCWarning(TEXTTRANSLATOR_LOG) << "Couldn't find a working backend for QNetworkInformation";
        return false;
    }
}

#include "moc_networkmanager.cpp"
