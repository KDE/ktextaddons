/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkserverinfo.h"

#include "autogeneratetext_genericnetwork_debug.h"

#include <KLocalizedString>
#include <QJsonObject>

#include <algorithm>

using namespace Qt::Literals::StringLiterals;
GenericNetworkServerInfo::GenericNetworkServerInfo() = default;

GenericNetworkServerInfo::~GenericNetworkServerInfo() = default;

QString GenericNetworkServerInfo::translatedName(GenericNetworkManager::PluginNetworkType type)
{
    switch (type) {
    case GenericNetworkManager::PluginNetworkType::Unknown:
        qCWarning(AUTOGENERATETEXT_GENERICNETWORK_LOG) << "PluginNetworkType is unknown. It's a bug";
        return {};
    case GenericNetworkManager::PluginNetworkType::MistralAI:
        return i18n("Mistral AI");
    case GenericNetworkManager::PluginNetworkType::NovitaAI:
        return i18n("Novita AI");
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
    case GenericNetworkManager::PluginNetworkType::GrokAI:
        return i18n("Grok (X.ai)");
    case GenericNetworkManager::PluginNetworkType::Qwen:
        return i18n("Qwen (DashScope)");
    case GenericNetworkManager::PluginNetworkType::DeepInfra:
        return i18n("DeepInfra");
    case GenericNetworkManager::PluginNetworkType::ChatGPT:
        return i18n("OpenAI ChatGPT");
    case GenericNetworkManager::PluginNetworkType::CompactifAI:
        return i18n("CompactifAI");
    case GenericNetworkManager::PluginNetworkType::OpenRouterAI:
        return i18n("OpenRouter AI");
    case GenericNetworkManager::PluginNetworkType::OrcaRouterAI:
        return i18n("OrcaRouter AI");
    case GenericNetworkManager::PluginNetworkType::SarvamAI:
        return i18n("Sarvam AI");
    case GenericNetworkManager::PluginNetworkType::AtlasCloud:
        return i18n("AtlasCloud OpenAI-compatible API");
    case GenericNetworkManager::PluginNetworkType::Gemini:
        return i18n("Google Gemini");
    case GenericNetworkManager::PluginNetworkType::OpenAIGeneric:
        return i18n("OpenAI API");
    case GenericNetworkManager::PluginNetworkType::DeepSeek:
        return i18n("DeepSeek");
    }
    return {};
}

QString GenericNetworkServerInfo::responsesPath(GenericNetworkManager::PluginNetworkType type)
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
    case GenericNetworkManager::PluginNetworkType::GrokAI:
    case GenericNetworkManager::PluginNetworkType::Qwen:
    case GenericNetworkManager::PluginNetworkType::NovitaAI:
    case GenericNetworkManager::PluginNetworkType::DeepInfra:
    case GenericNetworkManager::PluginNetworkType::ChatGPT:
    case GenericNetworkManager::PluginNetworkType::CompactifAI:
    case GenericNetworkManager::PluginNetworkType::OpenRouterAI:
    case GenericNetworkManager::PluginNetworkType::SarvamAI:
    case GenericNetworkManager::PluginNetworkType::AtlasCloud:
    case GenericNetworkManager::PluginNetworkType::Gemini:
    case GenericNetworkManager::PluginNetworkType::OrcaRouterAI:
    case GenericNetworkManager::PluginNetworkType::OpenAIGeneric:
    case GenericNetworkManager::PluginNetworkType::DeepSeek:
        return u"responses"_s;
    }
    return {};
}

QString GenericNetworkServerInfo::chatCompletionPath(GenericNetworkManager::PluginNetworkType type)
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
    case GenericNetworkManager::PluginNetworkType::GrokAI:
    case GenericNetworkManager::PluginNetworkType::Qwen:
    case GenericNetworkManager::PluginNetworkType::NovitaAI:
    case GenericNetworkManager::PluginNetworkType::DeepInfra:
    case GenericNetworkManager::PluginNetworkType::ChatGPT:
    case GenericNetworkManager::PluginNetworkType::CompactifAI:
    case GenericNetworkManager::PluginNetworkType::OpenRouterAI:
    case GenericNetworkManager::PluginNetworkType::SarvamAI:
    case GenericNetworkManager::PluginNetworkType::AtlasCloud:
    case GenericNetworkManager::PluginNetworkType::Gemini:
    case GenericNetworkManager::PluginNetworkType::OrcaRouterAI:
    case GenericNetworkManager::PluginNetworkType::OpenAIGeneric:
    case GenericNetworkManager::PluginNetworkType::DeepSeek:
        return u"chat/completions"_s;
    }
    return {};
}

QString GenericNetworkServerInfo::webSite(GenericNetworkManager::PluginNetworkType type)
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
    case GenericNetworkManager::PluginNetworkType::GrokAI:
        return u"https://api.x.ai/"_s;
    case GenericNetworkManager::PluginNetworkType::Qwen:
        return u"https://qwen.ai/home"_s;
    case GenericNetworkManager::PluginNetworkType::NovitaAI:
        return u"https://novita.ai/"_s;
    case GenericNetworkManager::PluginNetworkType::DeepInfra:
        return u"https://deepinfra.com/"_s;
    case GenericNetworkManager::PluginNetworkType::ChatGPT:
        return u"https://chatgpt.com/"_s;
    case GenericNetworkManager::PluginNetworkType::CompactifAI:
        return u"https://docs.compactif.ai/"_s;
    case GenericNetworkManager::PluginNetworkType::OpenRouterAI:
        return u"https://openrouter.ai/"_s;
    case GenericNetworkManager::PluginNetworkType::SarvamAI:
        return u"https://api.sarvam.ai/"_s;
    case GenericNetworkManager::PluginNetworkType::AtlasCloud:
        return u"https://www.atlascloud.ai/"_s;
    case GenericNetworkManager::PluginNetworkType::Gemini:
        return u"https://gemini.google.com"_s;
    case GenericNetworkManager::PluginNetworkType::OrcaRouterAI:
        return u"https://www.orcarouter.ai/"_s;
    case GenericNetworkManager::PluginNetworkType::OpenAIGeneric:
        return {};
    case GenericNetworkManager::PluginNetworkType::DeepSeek:
        return u"https://www.deepseek.com/"_s;
    }
    return {};
}

QString GenericNetworkServerInfo::apiUrl(GenericNetworkManager::PluginNetworkType type)
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
    case GenericNetworkManager::PluginNetworkType::GrokAI:
        return u"https://api.x.ai/v1/"_s;
    case GenericNetworkManager::PluginNetworkType::Qwen:
        return u"https://dashscope-intl.aliyuncs.com/compatible-mode/v1/"_s;
    case GenericNetworkManager::PluginNetworkType::NovitaAI:
        return u"https://api.novita.ai/v3/openai/"_s;
    case GenericNetworkManager::PluginNetworkType::DeepInfra:
        return u"https://api.deepinfra.com/v1/openai/"_s;
    case GenericNetworkManager::PluginNetworkType::ChatGPT:
        return u"https://api.openai.com/v1/"_s;
    case GenericNetworkManager::PluginNetworkType::CompactifAI:
        return u"https://api.compactif.ai/v1/"_s;
    case GenericNetworkManager::PluginNetworkType::OpenRouterAI:
        return u"https://openrouter.ai/api/v1/"_s;
    case GenericNetworkManager::PluginNetworkType::SarvamAI:
        return u"https://api.sarvam.ai/v1/"_s;
    case GenericNetworkManager::PluginNetworkType::AtlasCloud:
        return u"https://api.atlascloud.ai/v1/"_s;
    case GenericNetworkManager::PluginNetworkType::OrcaRouterAI:
        return u"https://api.orcarouter.ai/v1/"_s;
    case GenericNetworkManager::PluginNetworkType::Gemini:
        return u"https://generativelanguage.googleapis.com/v1beta/openai/"_s;
    case GenericNetworkManager::PluginNetworkType::OpenAIGeneric:
        return {};
    case GenericNetworkManager::PluginNetworkType::DeepSeek:
        return u"https://api.deepseek.com/v1/"_s;
    }
    return {};
}

QString GenericNetworkServerInfo::description(GenericNetworkManager::PluginNetworkType type)
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
    case GenericNetworkManager::PluginNetworkType::GrokAI:
    case GenericNetworkManager::PluginNetworkType::ChatGPT:
    case GenericNetworkManager::PluginNetworkType::Gemini:
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
    case GenericNetworkManager::PluginNetworkType::Qwen:
        return i18n("Alibaba Cloud Qwen large language models via DashScope");
    case GenericNetworkManager::PluginNetworkType::NovitaAI:
        return i18n("Novita AI cloud inference API");
    case GenericNetworkManager::PluginNetworkType::DeepInfra:
        return i18n("DeepInfra cloud inference API");
    case GenericNetworkManager::PluginNetworkType::CompactifAI:
        return i18n("CompactifAI");
    case GenericNetworkManager::PluginNetworkType::OpenRouterAI:
        return i18n("OpenRouter AI");
    case GenericNetworkManager::PluginNetworkType::SarvamAI:
        return i18n("Sarvam AI instance");
    case GenericNetworkManager::PluginNetworkType::AtlasCloud:
        return i18n("AtlasCloud OpenAI-compatible API");
    case GenericNetworkManager::PluginNetworkType::OrcaRouterAI:
        return i18n("OrcaRouter OpenAI-compatible API");
    case GenericNetworkManager::PluginNetworkType::OpenAIGeneric:
        return i18n("OpenAI API (custom)");
    case GenericNetworkManager::PluginNetworkType::DeepSeek:
        return i18n("DeepSeek large language models");
    }
    return {};
}

QString GenericNetworkServerInfo::pluginName(GenericNetworkManager::PluginNetworkType type)
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
    case GenericNetworkManager::PluginNetworkType::GrokAI:
        return u"grokai"_s;
    case GenericNetworkManager::PluginNetworkType::Qwen:
        return u"qwen"_s;
    case GenericNetworkManager::PluginNetworkType::NovitaAI:
        return u"novitaai"_s;
    case GenericNetworkManager::PluginNetworkType::DeepInfra:
        return u"deepinfra"_s;
    case GenericNetworkManager::PluginNetworkType::ChatGPT:
        return u"chatgpt"_s;
    case GenericNetworkManager::PluginNetworkType::CompactifAI:
        return u"compactifai"_s;
    case GenericNetworkManager::PluginNetworkType::OpenRouterAI:
        return u"openrouterai"_s;
    case GenericNetworkManager::PluginNetworkType::SarvamAI:
        return u"sarvamai"_s;
    case GenericNetworkManager::PluginNetworkType::AtlasCloud:
        return u"atlascloudai"_s;
    case GenericNetworkManager::PluginNetworkType::Gemini:
        return u"gemini"_s;
    case GenericNetworkManager::PluginNetworkType::OrcaRouterAI:
        return u"orcarouterai"_s;
    case GenericNetworkManager::PluginNetworkType::OpenAIGeneric:
        return u"openaigeneric"_s;
    case GenericNetworkManager::PluginNetworkType::DeepSeek:
        return u"deepseek"_s;
    }
    return {};
}

GenericNetworkManager::PluginNetworkType GenericNetworkServerInfo::pluginNetworkTypeFromString(const QString &str)
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
    } else if (str == QLatin1StringView("grokai")) {
        return GenericNetworkManager::PluginNetworkType::GrokAI;
    } else if (str == QLatin1StringView("qwen")) {
        return GenericNetworkManager::PluginNetworkType::Qwen;
    } else if (str == QLatin1StringView("novitaai")) {
        return GenericNetworkManager::PluginNetworkType::NovitaAI;
    } else if (str == QLatin1StringView("deepinfra")) {
        return GenericNetworkManager::PluginNetworkType::DeepInfra;
    } else if (str == QLatin1StringView("chatgpt")) {
        return GenericNetworkManager::PluginNetworkType::ChatGPT;
    } else if (str == QLatin1StringView("compactifai")) {
        return GenericNetworkManager::PluginNetworkType::CompactifAI;
    } else if (str == QLatin1StringView("openrouterai")) {
        return GenericNetworkManager::PluginNetworkType::OpenRouterAI;
    } else if (str == QLatin1StringView("sarvamai")) {
        return GenericNetworkManager::PluginNetworkType::SarvamAI;
    } else if (str == QLatin1StringView("atlascloudai")) {
        return GenericNetworkManager::PluginNetworkType::AtlasCloud;
    } else if (str == QLatin1StringView("gemini")) {
        return GenericNetworkManager::PluginNetworkType::Gemini;
    } else if (str == QLatin1StringView("orcarouterai")) {
        return GenericNetworkManager::PluginNetworkType::OrcaRouterAI;
    } else if (str == QLatin1StringView("openaigeneric")) {
        return GenericNetworkManager::PluginNetworkType::OpenAIGeneric;
    } else if (str == QLatin1StringView("deepseek")) {
        return GenericNetworkManager::PluginNetworkType::DeepSeek;
    } else {
        qCWarning(AUTOGENERATETEXT_GENERICNETWORK_LOG) << "PluginNetworkType is unknown. It's a bug" << str;
        return GenericNetworkManager::PluginNetworkType::Unknown;
    }
}

QList<TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer> GenericNetworkServerInfo::supportedServers(const QString &name)
{
    QList<TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer> listInfo;
    for (int i = static_cast<int>(GenericNetworkManager::PluginNetworkType::Unknown) + 1;
         i <= static_cast<int>(GenericNetworkManager::PluginNetworkType::LastElement);
         ++i) {
        TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer info{
            .localizedName = u"%1 (%2)"_s.arg(
                translatedName(static_cast<GenericNetworkManager::PluginNetworkType>(i)),
                TextAutoGenerateText::TextAutoGenerateTextPlugin::convertEngineType(TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType::Network)),
            .identifier = pluginName(static_cast<GenericNetworkManager::PluginNetworkType>(i)),
            .pluginName = name,
        };
        listInfo.append(std::move(info));
    }
    return listInfo;
}

bool GenericNetworkServerInfo::hasCustomUrl(GenericNetworkManager::PluginNetworkType type)
{
    if (type == GenericNetworkManager::PluginNetworkType::OpenAIGeneric) {
        return true;
    }
    return false;
}

QList<GenericNetworkModelAvailableInfo> GenericNetworkServerInfo::defaultModels(GenericNetworkManager::PluginNetworkType type)
{
    // Used when the server doesn't provide a "models" endpoint.
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
    case GenericNetworkManager::PluginNetworkType::GrokAI:
    case GenericNetworkManager::PluginNetworkType::Qwen:
    case GenericNetworkManager::PluginNetworkType::NovitaAI:
    case GenericNetworkManager::PluginNetworkType::DeepInfra:
    case GenericNetworkManager::PluginNetworkType::ChatGPT:
    case GenericNetworkManager::PluginNetworkType::CompactifAI:
    case GenericNetworkManager::PluginNetworkType::OpenRouterAI:
    case GenericNetworkManager::PluginNetworkType::SarvamAI:
    case GenericNetworkManager::PluginNetworkType::AtlasCloud:
    case GenericNetworkManager::PluginNetworkType::Gemini:
    case GenericNetworkManager::PluginNetworkType::OrcaRouterAI:
    case GenericNetworkManager::PluginNetworkType::OpenAIGeneric:
    case GenericNetworkManager::PluginNetworkType::DeepSeek:
        return {};
    }
    return {};
}

bool GenericNetworkServerInfo::modelSupportsTools(GenericNetworkManager::PluginNetworkType type, const QString &identifier)
{
    // Used when the "models" endpoint doesn't report tool support.
    switch (type) {
    case GenericNetworkManager::PluginNetworkType::Unknown:
        qCWarning(AUTOGENERATETEXT_GENERICNETWORK_LOG) << "PluginNetworkType is unknown. It's a bug";
        return false;
    case GenericNetworkManager::PluginNetworkType::Anthropic:
        // All Claude models support tools
        return true;
    case GenericNetworkManager::PluginNetworkType::Gemini: {
        // All Gemini chat models support function calling, the other models (embedding, image, tts…) don't
        static const QStringList nonChatModels{u"embedding"_s, u"imagen"_s, u"image"_s, u"tts"_s, u"veo"_s, u"aqa"_s, u"lyria"_s};
        return identifier.contains(u"gemini"_s) && std::none_of(nonChatModels.cbegin(), nonChatModels.cend(), [&identifier](const QString &str) {
                   return identifier.contains(str);
               });
    }
    case GenericNetworkManager::PluginNetworkType::DeepSeek:
        // DeepSeek models support OpenAI-compatible function calling
        return true;
    case GenericNetworkManager::PluginNetworkType::MistralAI:
    case GenericNetworkManager::PluginNetworkType::OpenAI:
    case GenericNetworkManager::PluginNetworkType::KlusterAI:
    case GenericNetworkManager::PluginNetworkType::GroqAI:
    case GenericNetworkManager::PluginNetworkType::VeniceAI:
    case GenericNetworkManager::PluginNetworkType::LlamaApi:
    case GenericNetworkManager::PluginNetworkType::CerebrasAI:
    case GenericNetworkManager::PluginNetworkType::KimiAI:
    case GenericNetworkManager::PluginNetworkType::GrokAI:
    case GenericNetworkManager::PluginNetworkType::Qwen:
    case GenericNetworkManager::PluginNetworkType::NovitaAI:
    case GenericNetworkManager::PluginNetworkType::DeepInfra:
    case GenericNetworkManager::PluginNetworkType::ChatGPT:
    case GenericNetworkManager::PluginNetworkType::CompactifAI:
    case GenericNetworkManager::PluginNetworkType::OpenRouterAI:
    case GenericNetworkManager::PluginNetworkType::SarvamAI:
    case GenericNetworkManager::PluginNetworkType::AtlasCloud:
    case GenericNetworkManager::PluginNetworkType::OrcaRouterAI:
        return false;
    case GenericNetworkManager::PluginNetworkType::OpenAIGeneric: {
        return identifier.contains(u"claude"_s) || identifier.contains(u"gemini"_s);
    }
    }
    return false;
}

GenericNetworkManager::Limitations GenericNetworkServerInfo::limitations(GenericNetworkManager::PluginNetworkType type)
{
    GenericNetworkManager::Limitations limits;
    switch (type) {
    case GenericNetworkManager::PluginNetworkType::Unknown:
        qCWarning(AUTOGENERATETEXT_GENERICNETWORK_LOG) << "PluginNetworkType is unknown. It's a bug";
        return limits;
    case GenericNetworkManager::PluginNetworkType::MistralAI:
    case GenericNetworkManager::PluginNetworkType::LlamaApi:
    case GenericNetworkManager::PluginNetworkType::OpenAI:
        return limits;
    case GenericNetworkManager::PluginNetworkType::GroqAI:
        limits |= GenericNetworkManager::Limitation::TextOnly;
        return limits;
    case GenericNetworkManager::PluginNetworkType::VeniceAI:
        limits |= GenericNetworkManager::Limitation::NoSystemMessage;
        return limits;
    case GenericNetworkManager::PluginNetworkType::KimiAI:
    case GenericNetworkManager::PluginNetworkType::NovitaAI:
    case GenericNetworkManager::PluginNetworkType::DeepSeek:
        limits |= GenericNetworkManager::Limitation::NoSeed;
        return limits;
    case GenericNetworkManager::PluginNetworkType::ChatGPT:
        limits |= GenericNetworkManager::Limitation::UseMaxCompletionTokens;
        return limits;
    case GenericNetworkManager::PluginNetworkType::KlusterAI:
    case GenericNetworkManager::PluginNetworkType::CerebrasAI:
    case GenericNetworkManager::PluginNetworkType::Anthropic:
    case GenericNetworkManager::PluginNetworkType::Gemini:
    case GenericNetworkManager::PluginNetworkType::GrokAI:
    case GenericNetworkManager::PluginNetworkType::Qwen:
    case GenericNetworkManager::PluginNetworkType::DeepInfra:
    case GenericNetworkManager::PluginNetworkType::CompactifAI:
    case GenericNetworkManager::PluginNetworkType::OpenRouterAI:
    case GenericNetworkManager::PluginNetworkType::OrcaRouterAI:
    case GenericNetworkManager::PluginNetworkType::SarvamAI:
    case GenericNetworkManager::PluginNetworkType::AtlasCloud:
    case GenericNetworkManager::PluginNetworkType::OpenAIGeneric:
        return limits;
    }
    return limits;
}

QList<GenericNetworkServerInfo::ThinkingLevel> GenericNetworkServerInfo::thinkingLevelList(GenericNetworkManager::PluginNetworkType type,
                                                                                           const QString &identifier)
{
    // Values accepted by "reasoning_effort" for each model. Empty list: no level (thinking is unsupported or can only be switched on/off).
    switch (type) {
    case GenericNetworkManager::PluginNetworkType::Unknown:
        qCWarning(AUTOGENERATETEXT_GENERICNETWORK_LOG) << "PluginNetworkType is unknown. It's a bug";
        return {};
    case GenericNetworkManager::PluginNetworkType::OpenAI:
    case GenericNetworkManager::PluginNetworkType::ChatGPT: {
        if (identifier.startsWith(u"o1"_s) || identifier.startsWith(u"o3"_s) || identifier.startsWith(u"o4"_s)) {
            return {ThinkingLevel::Low, ThinkingLevel::Medium, ThinkingLevel::High};
        }
        if (!identifier.startsWith(u"gpt-5"_s) || identifier.contains(u"-chat"_s)) {
            // gpt-4o, gpt-4.1, gpt-5-chat… are not reasoning models
            return {};
        }
        if (identifier.contains(u"-pro"_s)) {
            return {ThinkingLevel::High};
        }
        if (identifier.startsWith(u"gpt-5-"_s) || identifier == u"gpt-5"_s) {
            return {ThinkingLevel::Minimal, ThinkingLevel::Low, ThinkingLevel::Medium, ThinkingLevel::High};
        }
        if (identifier.startsWith(u"gpt-5.1"_s)) {
            return {ThinkingLevel::Disabled, ThinkingLevel::Low, ThinkingLevel::Medium, ThinkingLevel::High};
        }
        // gpt-5.2 and later
        return {ThinkingLevel::Disabled, ThinkingLevel::Low, ThinkingLevel::Medium, ThinkingLevel::High, ThinkingLevel::Xhigh};
    }
    case GenericNetworkManager::PluginNetworkType::Gemini: {
        if (identifier.contains(u"gemini-2.5"_s)) {
            if (identifier.contains(u"-pro"_s)) {
                // Thinking can't be disabled on 2.5 Pro
                return {ThinkingLevel::Low, ThinkingLevel::Medium, ThinkingLevel::High};
            }
            return {ThinkingLevel::Disabled, ThinkingLevel::Low, ThinkingLevel::Medium, ThinkingLevel::High};
        }
        if (identifier.contains(u"gemini-3"_s)) {
            if (identifier.contains(u"flash"_s)) {
                return {ThinkingLevel::Minimal, ThinkingLevel::Low, ThinkingLevel::Medium, ThinkingLevel::High};
            }
            return {ThinkingLevel::Low, ThinkingLevel::High};
        }
        return {};
    }
    case GenericNetworkManager::PluginNetworkType::GrokAI:
        // Only grok-3-mini accepts reasoning_effort, grok-4 always reasons
        if (identifier.startsWith(u"grok-3-mini"_s)) {
            return {ThinkingLevel::Low, ThinkingLevel::High};
        }
        return {};
    case GenericNetworkManager::PluginNetworkType::OpenAIGeneric:
        // Unknown server: use the values that every reasoning_effort implementation accepts
        return {ThinkingLevel::Low, ThinkingLevel::Medium, ThinkingLevel::High};
    case GenericNetworkManager::PluginNetworkType::Anthropic:
        // Uses a token budget ("thinking": {"budget_tokens"}), not named levels.
        // Extended thinking exists since Claude 3.7
        if (identifier.startsWith(u"claude-3-"_s) && !identifier.startsWith(u"claude-3-7"_s)) {
            return {};
        }
        return {ThinkingLevel::Disabled, ThinkingLevel::Enabled};
    case GenericNetworkManager::PluginNetworkType::DeepSeek:
    case GenericNetworkManager::PluginNetworkType::Qwen:
        // Thinking can only be switched on or off
        return {ThinkingLevel::Disabled, ThinkingLevel::Enabled};
    case GenericNetworkManager::PluginNetworkType::MistralAI:
    case GenericNetworkManager::PluginNetworkType::KlusterAI:
    case GenericNetworkManager::PluginNetworkType::GroqAI:
    case GenericNetworkManager::PluginNetworkType::VeniceAI:
    case GenericNetworkManager::PluginNetworkType::LlamaApi:
    case GenericNetworkManager::PluginNetworkType::CerebrasAI:
    case GenericNetworkManager::PluginNetworkType::KimiAI:
    case GenericNetworkManager::PluginNetworkType::NovitaAI:
    case GenericNetworkManager::PluginNetworkType::DeepInfra:
    case GenericNetworkManager::PluginNetworkType::CompactifAI:
    case GenericNetworkManager::PluginNetworkType::OpenRouterAI:
    case GenericNetworkManager::PluginNetworkType::SarvamAI:
    case GenericNetworkManager::PluginNetworkType::AtlasCloud:
    case GenericNetworkManager::PluginNetworkType::OrcaRouterAI:
        return {};
    }
    return {};
}

QString GenericNetworkServerInfo::thinkingLevelI18n(GenericNetworkServerInfo::ThinkingLevel level)
{
    switch (level) {
    case GenericNetworkServerInfo::ThinkingLevel::Disabled:
        return i18nc("@item:inlistbox thinking level", "Disabled");
    case GenericNetworkServerInfo::ThinkingLevel::Enabled:
        return i18nc("@item:inlistbox thinking level", "Enabled");
    case GenericNetworkServerInfo::ThinkingLevel::Minimal:
        return i18nc("@item:inlistbox thinking level", "Minimal");
    case GenericNetworkServerInfo::ThinkingLevel::Low:
        return i18nc("@item:inlistbox thinking level", "Low");
    case GenericNetworkServerInfo::ThinkingLevel::Medium:
        return i18nc("@item:inlistbox thinking level", "Medium");
    case GenericNetworkServerInfo::ThinkingLevel::High:
        return i18nc("@item:inlistbox thinking level", "High");
    case GenericNetworkServerInfo::ThinkingLevel::Xhigh:
        return i18nc("@item:inlistbox thinking level", "Extra High");
    case GenericNetworkServerInfo::ThinkingLevel::Unknown:
        return {};
    }
    return {};
}

QString GenericNetworkServerInfo::thinkingLevel(GenericNetworkServerInfo::ThinkingLevel level)
{
    switch (level) {
    case GenericNetworkServerInfo::ThinkingLevel::Disabled:
        return u"none"_s;
    case GenericNetworkServerInfo::ThinkingLevel::Enabled:
        return u"enabled"_s;
    case GenericNetworkServerInfo::ThinkingLevel::Minimal:
        return u"minimal"_s;
    case GenericNetworkServerInfo::ThinkingLevel::Low:
        return u"low"_s;
    case GenericNetworkServerInfo::ThinkingLevel::Medium:
        return u"medium"_s;
    case GenericNetworkServerInfo::ThinkingLevel::High:
        return u"high"_s;
    case GenericNetworkServerInfo::ThinkingLevel::Xhigh:
        return u"xhigh"_s;
    case GenericNetworkServerInfo::ThinkingLevel::Unknown:
        return {};
    }
    return {};
}

bool GenericNetworkServerInfo::isThinkingLevelSupported(GenericNetworkManager::PluginNetworkType type, const QString &identifier, const QString &level)
{
    const QList<ThinkingLevel> levels = thinkingLevelList(type, identifier);
    return std::ranges::any_of(levels, [&level](ThinkingLevel l) {
        return thinkingLevel(l) == level;
    });
}

void GenericNetworkServerInfo::thinkingJson(QJsonObject &data,
                                            const QString &level,
                                            GenericNetworkManager::PluginNetworkType type,
                                            GenericNetworkManager::ApiType api)
{
    if (level.isEmpty()) {
        return;
    }
    if (api == GenericNetworkManager::ApiType::Responses) {
        // Other providers only expose chat/completions
        if (type == GenericNetworkManager::PluginNetworkType::OpenAI || type == GenericNetworkManager::PluginNetworkType::ChatGPT
            || type == GenericNetworkManager::PluginNetworkType::GrokAI || type == GenericNetworkManager::PluginNetworkType::OpenAIGeneric) {
            QJsonObject reasoning;
            reasoning["effort"_L1] = level;
            data["reasoning"_L1] = reasoning;
        }
        return;
    }
    const bool disabled = (level == thinkingLevel(ThinkingLevel::Disabled));
    switch (type) {
    case GenericNetworkManager::PluginNetworkType::Unknown:
        qCWarning(AUTOGENERATETEXT_GENERICNETWORK_LOG) << "PluginNetworkType is unknown. It's a bug";
        return;
    case GenericNetworkManager::PluginNetworkType::OpenAI:
    case GenericNetworkManager::PluginNetworkType::ChatGPT:
    case GenericNetworkManager::PluginNetworkType::Gemini:
    case GenericNetworkManager::PluginNetworkType::GrokAI:
    case GenericNetworkManager::PluginNetworkType::OpenAIGeneric:
        // "none" is a valid reasoning_effort value (gpt-5.1+, gemini-2.5-flash)
        data["reasoning_effort"_L1] = level;
        return;
    case GenericNetworkManager::PluginNetworkType::Anthropic: {
        // Thinking is off by default
        if (disabled) {
            return;
        }
        QJsonObject thinking;
        thinking["type"_L1] = u"enabled"_s;
        thinking["budget_tokens"_L1] = 2048;
        data["thinking"_L1] = thinking;
        return;
    }
    case GenericNetworkManager::PluginNetworkType::DeepSeek: {
        QJsonObject thinking;
        thinking["type"_L1] = disabled ? u"disabled"_s : u"enabled"_s;
        data["thinking"_L1] = thinking;
        return;
    }
    case GenericNetworkManager::PluginNetworkType::Qwen:
        // Default depends on the model, so always send it
        data["enable_thinking"_L1] = !disabled;
        return;
    case GenericNetworkManager::PluginNetworkType::MistralAI:
    case GenericNetworkManager::PluginNetworkType::KlusterAI:
    case GenericNetworkManager::PluginNetworkType::GroqAI:
    case GenericNetworkManager::PluginNetworkType::VeniceAI:
    case GenericNetworkManager::PluginNetworkType::LlamaApi:
    case GenericNetworkManager::PluginNetworkType::CerebrasAI:
    case GenericNetworkManager::PluginNetworkType::KimiAI:
    case GenericNetworkManager::PluginNetworkType::NovitaAI:
    case GenericNetworkManager::PluginNetworkType::DeepInfra:
    case GenericNetworkManager::PluginNetworkType::CompactifAI:
    case GenericNetworkManager::PluginNetworkType::OpenRouterAI:
    case GenericNetworkManager::PluginNetworkType::SarvamAI:
    case GenericNetworkManager::PluginNetworkType::AtlasCloud:
    case GenericNetworkManager::PluginNetworkType::OrcaRouterAI:
        return;
    }
}

#include "moc_genericnetworkserverinfo.cpp"
