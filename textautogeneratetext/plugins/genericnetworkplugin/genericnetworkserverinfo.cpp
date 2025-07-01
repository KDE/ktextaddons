/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkserverinfo.h"

#include "autogeneratetext_genericnetwork_debug.h"

#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;
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
    case GenericNetworkManager::PluginNetworkType::GroqAI:
        return i18n("Groq Cloud");
    case GenericNetworkManager::PluginNetworkType::LastElement:
        return {};
    }
    return {};
}

QString GenericNetworkServerInfo::chatCompletionPath(GenericNetworkManager::PluginNetworkType type) const
{
    switch (type) {
    case GenericNetworkManager::PluginNetworkType::Unknown:
        qCWarning(AUTOGENERATETEXT_GENERICNETWORK_LOG) << "PluginNetworkType is unknown. It's a bug";
        return {};
    case GenericNetworkManager::PluginNetworkType::MistralAI:
    case GenericNetworkManager::PluginNetworkType::OpenAI:
    case GenericNetworkManager::PluginNetworkType::KlusterAI:
    case GenericNetworkManager::PluginNetworkType::GroqAI:
        return u"chat/completions"_s;
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
        return u"https://mistral.ai/"_s;
    case GenericNetworkManager::PluginNetworkType::OpenAI:
        return u"https://openai.com/"_s;
    case GenericNetworkManager::PluginNetworkType::KlusterAI:
        return u"https://www.kluster.ai/"_s;
    case GenericNetworkManager::PluginNetworkType::GroqAI:
        return u"https://groq.com/"_s;
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
        return u"https://api.mistral.ai/v1/"_s;
    case GenericNetworkManager::PluginNetworkType::OpenAI:
        return u"https://api.openai.com/v1/"_s;
    case GenericNetworkManager::PluginNetworkType::KlusterAI:
        return u"https://api.kluster.ai/v1/"_s;
    case GenericNetworkManager::PluginNetworkType::GroqAI:
        return u"https://api.groq.com/openai/v1/"_s;
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
        return i18n("Mistral AI large language models");
    case GenericNetworkManager::PluginNetworkType::OpenAI:
    case GenericNetworkManager::PluginNetworkType::GroqAI:
        return {};
    case GenericNetworkManager::PluginNetworkType::KlusterAI:
        return i18n("Kluster AI cloud inference API");
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
        return u"mistralai"_s;
    case GenericNetworkManager::PluginNetworkType::OpenAI:
        return u"openai"_s;
    case GenericNetworkManager::PluginNetworkType::KlusterAI:
        return u"klusterai"_s;
    case GenericNetworkManager::PluginNetworkType::GroqAI:
        return u"groqai"_s;
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
    } else if (str == QLatin1StringView("groqai")) {
        return GenericNetworkManager::PluginNetworkType::GroqAI;
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

GenericNetworkServerInfo::Limitations GenericNetworkServerInfo::limitations(GenericNetworkManager::PluginNetworkType type) const
{
    return {};
}
