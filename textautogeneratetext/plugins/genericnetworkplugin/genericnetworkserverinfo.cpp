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
    case GenericNetworkManager::PluginNetworkType::CerebrasAI:
        return i18n("Cerebras AI");
    case GenericNetworkManager::PluginNetworkType::VeniceAI:
        return i18n("Venice");
    case GenericNetworkManager::PluginNetworkType::LlamaApi:
        return i18n("Llama Api");
    case GenericNetworkManager::PluginNetworkType::Anthropic:
        return i18n("Anthropic");
    case GenericNetworkManager::PluginNetworkType::KimiAI:
        return i18n("Kimi (Moonshot AI)");
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
    case GenericNetworkManager::PluginNetworkType::VeniceAI:
    case GenericNetworkManager::PluginNetworkType::LlamaApi:
    case GenericNetworkManager::PluginNetworkType::CerebrasAI:
    case GenericNetworkManager::PluginNetworkType::Anthropic:
    case GenericNetworkManager::PluginNetworkType::KimiAI:
        return u"chat/completions"_s;
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
    case GenericNetworkManager::PluginNetworkType::CerebrasAI:
        return u"https://www.cerebras.ai/"_s;
    case GenericNetworkManager::PluginNetworkType::VeniceAI:
        return u"https://www.venice.ai/"_s;
    case GenericNetworkManager::PluginNetworkType::LlamaApi:
        return u"https://www.llama.com/products/llama-api/"_s;
    case GenericNetworkManager::PluginNetworkType::Anthropic:
        return u"https://www.anthropic.com/"_s;
    case GenericNetworkManager::PluginNetworkType::KimiAI:
        return u"https://www.moonshot.ai/"_s;
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
    case GenericNetworkManager::PluginNetworkType::CerebrasAI:
        return u"https://api.cerebras.ai/v1/"_s;
    case GenericNetworkManager::PluginNetworkType::VeniceAI:
        return u"https://api.venice.ai/api/v1/"_s;
    case GenericNetworkManager::PluginNetworkType::LlamaApi:
        return u"https://api.llama.com/compat/v1/"_s;
    case GenericNetworkManager::PluginNetworkType::Anthropic:
        return u"https://api.anthropic.com/v1/"_s;
    case GenericNetworkManager::PluginNetworkType::KimiAI:
        return u"https://api.moonshot.ai/v1/"_s;
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
    case GenericNetworkManager::PluginNetworkType::VeniceAI:
    case GenericNetworkManager::PluginNetworkType::Anthropic:
        return {};
    case GenericNetworkManager::PluginNetworkType::GroqAI:
        return i18n("Groq AI");
    case GenericNetworkManager::PluginNetworkType::KlusterAI:
        return i18n("Kluster AI cloud inference API");
    case GenericNetworkManager::PluginNetworkType::CerebrasAI:
        return i18n("Cerebras AI cloud inference API");
    case GenericNetworkManager::PluginNetworkType::LlamaApi:
        return i18n("Meta AI Llama API");
    case GenericNetworkManager::PluginNetworkType::KimiAI:
        return i18n("Kimi large language models by Moonshot AI");
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
    case GenericNetworkManager::PluginNetworkType::CerebrasAI:
        return u"cerebrasai"_s;
    case GenericNetworkManager::PluginNetworkType::VeniceAI:
        return u"veniceai"_s;
    case GenericNetworkManager::PluginNetworkType::LlamaApi:
        return u"llamaapi"_s;
    case GenericNetworkManager::PluginNetworkType::Anthropic:
        return u"anthropic"_s;
    case GenericNetworkManager::PluginNetworkType::KimiAI:
        return u"kimiai"_s;
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
    } else if (str == QLatin1StringView("cerebrasai")) {
        return GenericNetworkManager::PluginNetworkType::CerebrasAI;
    } else if (str == QLatin1StringView("veniceai")) {
        return GenericNetworkManager::PluginNetworkType::VeniceAI;
    } else if (str == QLatin1StringView("llamaapi")) {
        return GenericNetworkManager::PluginNetworkType::LlamaApi;
    } else if (str == QLatin1StringView("anthropic")) {
        return GenericNetworkManager::PluginNetworkType::Anthropic;
    } else if (str == QLatin1StringView("kimiai")) {
        return GenericNetworkManager::PluginNetworkType::KimiAI;
    } else {
        qCWarning(AUTOGENERATETEXT_GENERICNETWORK_LOG) << "PluginNetworkType is unknown. It's a bug" << str;
        return GenericNetworkManager::PluginNetworkType::Unknown;
    }
}

QList<TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer> GenericNetworkServerInfo::supportedServers(const QString &name) const
{
    QList<TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer> listInfo;
    for (int i = static_cast<int>(GenericNetworkManager::PluginNetworkType::Unknown) + 1;
         i <= static_cast<int>(GenericNetworkManager::PluginNetworkType::LastElement);
         ++i) {
        const TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer info{
            .localizedName = QStringLiteral("%1 (%2)").arg(
                translatedName(static_cast<GenericNetworkManager::PluginNetworkType>(i)),
                TextAutoGenerateText::TextAutoGenerateTextPlugin::convertEngineType(TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType::Network)),
            .identifier = pluginName(static_cast<GenericNetworkManager::PluginNetworkType>(i)),
            .pluginName = name,
        };
        listInfo.append(info);
    }
    return listInfo;
}

GenericNetworkServerInfo::Limitations GenericNetworkServerInfo::limitations(GenericNetworkManager::PluginNetworkType type) const
{
    GenericNetworkServerInfo::Limitations limits;
    limits |= GenericNetworkServerInfo::Limitation::None;
    switch (type) {
    case GenericNetworkManager::PluginNetworkType::Unknown:
        qCWarning(AUTOGENERATETEXT_GENERICNETWORK_LOG) << "PluginNetworkType is unknown. It's a bug";
        return limits;
    case GenericNetworkManager::PluginNetworkType::MistralAI:
    case GenericNetworkManager::PluginNetworkType::LlamaApi:
    case GenericNetworkManager::PluginNetworkType::OpenAI:
        return limits;
    case GenericNetworkManager::PluginNetworkType::GroqAI:
        limits |= GenericNetworkServerInfo::Limitation::TextOnly;
        return limits;
    case GenericNetworkManager::PluginNetworkType::VeniceAI:
        limits |= GenericNetworkServerInfo::Limitation::NoSystemMessage;
        return limits;
    case GenericNetworkManager::PluginNetworkType::KimiAI:
        limits |= GenericNetworkServerInfo::Limitation::NoSystemMessage;
        return limits;
    case GenericNetworkManager::PluginNetworkType::KlusterAI:
    case GenericNetworkManager::PluginNetworkType::CerebrasAI:
    case GenericNetworkManager::PluginNetworkType::Anthropic:
        return limits;
    }
    return limits;
}

bool GenericNetworkServerInfo::hasVisionSupport(const QString &currentModel, GenericNetworkManager::PluginNetworkType type) const
{
    switch (type) {
    case GenericNetworkManager::PluginNetworkType::Unknown:
        qCWarning(AUTOGENERATETEXT_GENERICNETWORK_LOG) << "PluginNetworkType is unknown. It's a bug";
        return false;
    case GenericNetworkManager::PluginNetworkType::MistralAI:
        if (currentModel == "pixtral-12b-latest"_L1 || currentModel == "pixtral-large-latest"_L1 || currentModel == "mistral-medium-2508"_L1
            || currentModel == "mistral-small-2506"_L1) {
            return true;
        }
        return false;
    case GenericNetworkManager::PluginNetworkType::LlamaApi:
    case GenericNetworkManager::PluginNetworkType::OpenAI:
    case GenericNetworkManager::PluginNetworkType::GroqAI:
    case GenericNetworkManager::PluginNetworkType::VeniceAI:
    case GenericNetworkManager::PluginNetworkType::KimiAI:
    case GenericNetworkManager::PluginNetworkType::KlusterAI:
    case GenericNetworkManager::PluginNetworkType::CerebrasAI:
    case GenericNetworkManager::PluginNetworkType::Anthropic:
        return false;
    }
    return false;
}

bool GenericNetworkServerInfo::hasToolsSupport(const QString &currentModel, GenericNetworkManager::PluginNetworkType type) const
{
    qDebug() << " bool GenericNetworkServerInfo::hasToolsSupport(const QString &currentModel, GenericNetworkManager::PluginNetworkType type) const"
             << currentModel << " type " << static_cast<int>(type);
    switch (type) {
    case GenericNetworkManager::PluginNetworkType::Unknown:
        qCWarning(AUTOGENERATETEXT_GENERICNETWORK_LOG) << "PluginNetworkType is unknown. It's a bug";
        return false;
    case GenericNetworkManager::PluginNetworkType::MistralAI: {
        // https://docs.mistral.ai/capabilities/function_calling/#tools
        qDebug() << " currentModel " << currentModel;
        if (currentModel == "Mistral Large"_L1) {
            return true;
        }
#if 0
        Mistral Large
        Mistral Medium
        Magistral Medium
        Mistral Small
        Magistral Small
        Devstral Small
        Devstral Medium
        Voxtral Small
        Voxtral Mini
        Codestral
        Ministral 8B
        Ministral 3B
        Pixtral 12B
        Pixtral Large
        Mistral Nemo
#endif
        return false;
    }
    case GenericNetworkManager::PluginNetworkType::LlamaApi:
    case GenericNetworkManager::PluginNetworkType::OpenAI:
    case GenericNetworkManager::PluginNetworkType::GroqAI:
    case GenericNetworkManager::PluginNetworkType::VeniceAI:
    case GenericNetworkManager::PluginNetworkType::KimiAI:
    case GenericNetworkManager::PluginNetworkType::KlusterAI:
    case GenericNetworkManager::PluginNetworkType::CerebrasAI:
    case GenericNetworkManager::PluginNetworkType::Anthropic:
        return false;
    }
    return false;
}
