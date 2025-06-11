/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkserverinfo.h"
#include "autogeneratetext_genericnetwork_debug.h"

#include <KLocalizedString>

GenericNetworkServerInfo::GenericNetworkServerInfo() = default;

GenericNetworkServerInfo::~GenericNetworkServerInfo() = default;

QString GenericNetworkServerInfo::translatedName(GenericNetworkManager::PluginNetworkType type) const
{
    switch (type) {
    case GenericNetworkManager::PluginNetworkType::Unknown:
        qCWarning(AUTOGENERATETEXT_GENERICNETWORK_LOG) << "PluginNetworkType is unknown. It's a bug";
        return {};
    case GenericNetworkManager::PluginNetworkType::MistralAI:
        return i18n("Mistral AI");
    case GenericNetworkManager::PluginNetworkType::OpenAI:
        return i18n("OpenAI");
    case GenericNetworkManager::PluginNetworkType::LastElement:
        return {};
    }
    return {};
}

QString GenericNetworkServerInfo::webSite(GenericNetworkManager::PluginNetworkType type) const
{
    switch (type) {
    case GenericNetworkManager::PluginNetworkType::Unknown:
        qCWarning(AUTOGENERATETEXT_GENERICNETWORK_LOG) << "PluginNetworkType is unknown. It's a bug";
        return {};
    case GenericNetworkManager::PluginNetworkType::MistralAI:
        return {};
    case GenericNetworkManager::PluginNetworkType::OpenAI:
        return {};
    case GenericNetworkManager::PluginNetworkType::LastElement:
        return {};
    }
    return {};
}

QString GenericNetworkServerInfo::apiUrl(GenericNetworkManager::PluginNetworkType type) const
{
    switch (type) {
    case GenericNetworkManager::PluginNetworkType::Unknown:
        qCWarning(AUTOGENERATETEXT_GENERICNETWORK_LOG) << "PluginNetworkType is unknown. It's a bug";
        return {};
    case GenericNetworkManager::PluginNetworkType::MistralAI:
        return QStringLiteral("https://chat.mistral.ai/");
    case GenericNetworkManager::PluginNetworkType::OpenAI:
        return QStringLiteral("https://api.openai.com/v1/");
    case GenericNetworkManager::PluginNetworkType::LastElement:
        return {};
    }
    return {};
}

QString GenericNetworkServerInfo::description(GenericNetworkManager::PluginNetworkType type) const
{
    switch (type) {
    case GenericNetworkManager::PluginNetworkType::Unknown:
        qCWarning(AUTOGENERATETEXT_GENERICNETWORK_LOG) << "PluginNetworkType is unknown. It's a bug";
        return {};
    case GenericNetworkManager::PluginNetworkType::MistralAI:
        return {};
    case GenericNetworkManager::PluginNetworkType::OpenAI:
        return {};
    case GenericNetworkManager::PluginNetworkType::LastElement:
        return {};
    }
    return {};
}

QString GenericNetworkServerInfo::pluginName(GenericNetworkManager::PluginNetworkType type) const
{
    switch (type) {
    case GenericNetworkManager::PluginNetworkType::Unknown:
        qCWarning(AUTOGENERATETEXT_GENERICNETWORK_LOG) << "PluginNetworkType is unknown. It's a bug";
        return {};
    case GenericNetworkManager::PluginNetworkType::MistralAI:
        return QStringLiteral("mistralai");
    case GenericNetworkManager::PluginNetworkType::OpenAI:
        return QStringLiteral("openai");
    case GenericNetworkManager::PluginNetworkType::LastElement:
        return {};
    }
    return {};
}

QList<TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer> GenericNetworkServerInfo::supportedServers(const QString &name) const
{
    QList<TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer> listInfo;
    for (int i = static_cast<int>(GenericNetworkManager::PluginNetworkType::Unknown) + 1;
         i < static_cast<int>(GenericNetworkManager::PluginNetworkType::Unknown);
         ++i) {
        TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer info;
        info.serverName = translatedName(static_cast<GenericNetworkManager::PluginNetworkType>(i));
        info.identifier = pluginName(static_cast<GenericNetworkManager::PluginNetworkType>(i));
        info.pluginName = name;
        listInfo.append(std::move(info));
    }
    return listInfo;
}
