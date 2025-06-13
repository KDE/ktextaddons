/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkmanager.h"
#include "genericnetworkserverinfo.h"
#include <KLocalizedString>

GenericNetworkManager::GenericNetworkManager(QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateManagerBase{parent}
{
}

GenericNetworkManager::~GenericNetworkManager() = default;

void GenericNetworkManager::loadModels()
{
    // TODO
}

GenericNetworkManager::PluginNetworkType GenericNetworkManager::pluginNetworkType() const
{
    return mPluginNetworkType;
}

void GenericNetworkManager::setPluginNetworkType(PluginNetworkType newPluginNetworkType)
{
    mPluginNetworkType = newPluginNetworkType;
}

QString GenericNetworkManager::translatedName() const
{
    const GenericNetworkServerInfo info;
    return info.translatedName(mPluginNetworkType);
}

QString GenericNetworkManager::webSite() const
{
    const GenericNetworkServerInfo info;
    return info.webSite(mPluginNetworkType);
}

QString GenericNetworkManager::apiUrl() const
{
    const GenericNetworkServerInfo info;
    return info.apiUrl(mPluginNetworkType);
}

QString GenericNetworkManager::description() const
{
    const GenericNetworkServerInfo info;
    return info.description(mPluginNetworkType);
}

QString GenericNetworkManager::pluginName() const
{
    const GenericNetworkServerInfo info;
    return info.pluginName(mPluginNetworkType);
}

QString GenericNetworkManager::apiKey() const
{
    return mApiKey;
}

void GenericNetworkManager::setApiKey(const QString &newApiKey)
{
    mApiKey = newApiKey;
}

#include "moc_genericnetworkmanager.cpp"
