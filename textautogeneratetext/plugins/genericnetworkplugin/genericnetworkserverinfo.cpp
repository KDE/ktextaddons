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
    case GenericNetworkManager::PluginNetworkType::KlusterAI:
        return i18n("Kluster AI");
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
        return QStringLiteral("https://openai.com/");
    case GenericNetworkManager::PluginNetworkType::KlusterAI:
        return QStringLiteral("https://www.kluster.ai/");
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
    case GenericNetworkManager::PluginNetworkType::KlusterAI:
        return QStringLiteral("https://api.kluster.ai/v1/");
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
    case GenericNetworkManager::PluginNetworkType::KlusterAI:
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
    case GenericNetworkManager::PluginNetworkType::KlusterAI:
        return QStringLiteral("klusterai");
    case GenericNetworkManager::PluginNetworkType::LastElement:
        return {};
    }
    return {};
}

GenericNetworkManager::PluginNetworkType GenericNetworkServerInfo::pluginNetworkTypeFromString(const QString &str) const
{
    if (str == QLatin1StringView("mistralai")) {
        return GenericNetworkManager::PluginNetworkType::MistralAI;
    } else if (str == QLatin1StringView("openai")) {
        return GenericNetworkManager::PluginNetworkType::OpenAI;
    } else if (str == QLatin1StringView("klusterai")) {
        return GenericNetworkManager::PluginNetworkType::KlusterAI;
    } else {
        qCWarning(AUTOGENERATETEXT_GENERICNETWORK_LOG) << "PluginNetworkType is unknown. It's a bug" << str;
        return GenericNetworkManager::PluginNetworkType::Unknown;
    }
}

QList<TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer> GenericNetworkServerInfo::supportedServers(const QString &name) const
{
    QList<TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer> listInfo;
    for (int i = static_cast<int>(GenericNetworkManager::PluginNetworkType::Unknown) + 1;
         i < static_cast<int>(GenericNetworkManager::PluginNetworkType::LastElement);
         ++i) {
        const TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer info{
            .localizedName = translatedName(static_cast<GenericNetworkManager::PluginNetworkType>(i)),
            .identifier = pluginName(static_cast<GenericNetworkManager::PluginNetworkType>(i)),
            .pluginName = name,
        };
        listInfo.append(std::move(info));
    }
    return listInfo;
}
