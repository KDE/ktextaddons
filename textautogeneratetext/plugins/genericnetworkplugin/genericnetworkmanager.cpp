/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkmanager.h"
#include "autogeneratetext_genericnetwork_debug.h"
#include <KLocalizedString>

GenericNetworkManager::GenericNetworkManager(QObject *parent)
    : QObject{parent}
{
}

GenericNetworkManager::~GenericNetworkManager() = default;

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
    switch (mPluginNetworkType) {
    case PluginNetworkType::Unknown:
        qCWarning(AUTOGENERATETEXT_GENERICNETWORK_LOG) << "PluginNetworkType is unknown. It's a bug";
        return {};
    case PluginNetworkType::MistralAI:
        return {};
    case PluginNetworkType::OpenAI:
        return {};
    }
    return {};
}

QString GenericNetworkManager::webSite() const
{
    switch (mPluginNetworkType) {
    case PluginNetworkType::Unknown:
        qCWarning(AUTOGENERATETEXT_GENERICNETWORK_LOG) << "PluginNetworkType is unknown. It's a bug";
        return {};
    case PluginNetworkType::MistralAI:
        return {};
    case PluginNetworkType::OpenAI:
        return {};
    }
    return {};
}

QString GenericNetworkManager::apiUrl() const
{
    switch (mPluginNetworkType) {
    case PluginNetworkType::Unknown:
        qCWarning(AUTOGENERATETEXT_GENERICNETWORK_LOG) << "PluginNetworkType is unknown. It's a bug";
        return {};
    case PluginNetworkType::MistralAI:
        return {};
    case PluginNetworkType::OpenAI:
        return {};
    }
    return {};
}

#include "moc_genericnetworkmanager.cpp"
