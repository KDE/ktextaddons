/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkserverinfotest.h"

#include "genericnetworkserverinfo.h"
#include <QTest>
QTEST_GUILESS_MAIN(GenericNetworkServerInfoTest)

using namespace Qt::Literals::StringLiterals;
GenericNetworkServerInfoTest::GenericNetworkServerInfoTest(QObject *parent)
    : QObject{parent}
{
}

void GenericNetworkServerInfoTest::shouldConvertPluginNetworkTypeFromString()
{
    const GenericNetworkServerInfo info;
    QCOMPARE(info.pluginNetworkTypeFromString(u"mistralai"_s), GenericNetworkManager::PluginNetworkType::MistralAI);
    QCOMPARE(info.pluginNetworkTypeFromString(u"openai"_s), GenericNetworkManager::PluginNetworkType::OpenAI);
    QCOMPARE(info.pluginNetworkTypeFromString(QString()), GenericNetworkManager::PluginNetworkType::Unknown);
    QCOMPARE(info.pluginNetworkTypeFromString(u"openaisdfsdf"_s), GenericNetworkManager::PluginNetworkType::Unknown);
    QCOMPARE(info.pluginNetworkTypeFromString(u"groqai"_s), GenericNetworkManager::PluginNetworkType::GroqAI);
    QCOMPARE(info.pluginNetworkTypeFromString(u"cerebrasai"_s), GenericNetworkManager::PluginNetworkType::CerebrasAI);
    QCOMPARE(info.pluginNetworkTypeFromString(u"veniceai"_s), GenericNetworkManager::PluginNetworkType::VeniceAI);
    QCOMPARE(info.pluginNetworkTypeFromString(u"llamaapi"_s), GenericNetworkManager::PluginNetworkType::LlamaApi);
    QCOMPARE(info.pluginNetworkTypeFromString(u"anthropic"_s), GenericNetworkManager::PluginNetworkType::Anthropic);
    QCOMPARE(info.pluginNetworkTypeFromString(u"kimiai"_s), GenericNetworkManager::PluginNetworkType::KimiAI);
    QCOMPARE(info.pluginNetworkTypeFromString(u"grokai"_s), GenericNetworkManager::PluginNetworkType::GrokAI);
    QCOMPARE(info.pluginNetworkTypeFromString(u"qwen"_s), GenericNetworkManager::PluginNetworkType::Qwen);
    QCOMPARE(info.pluginNetworkTypeFromString(u"novitaai"_s), GenericNetworkManager::PluginNetworkType::NovitaAI);
    QCOMPARE(info.pluginNetworkTypeFromString(u"deepinfra"_s), GenericNetworkManager::PluginNetworkType::DeepInfra);
    QCOMPARE(info.pluginNetworkTypeFromString(u"chatgpt"_s), GenericNetworkManager::PluginNetworkType::ChatGPT);
    QCOMPARE(info.pluginNetworkTypeFromString(u"compactifai"_s), GenericNetworkManager::PluginNetworkType::CompactifAI);
}

void GenericNetworkServerInfoTest::shouldCheckApiUrl()
{
    const GenericNetworkServerInfo info;
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::MistralAI), u"https://api.mistral.ai/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::OpenAI), u"https://api.openai.com/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::KlusterAI), u"https://api.kluster.ai/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::GroqAI), u"https://api.groq.com/openai/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::CerebrasAI), u"https://api.cerebras.ai/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::VeniceAI), u"https://api.venice.ai/api/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::LlamaApi), u"https://api.llama.com/compat/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::Anthropic), u"https://api.anthropic.com/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::KimiAI), u"https://api.moonshot.ai/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::GrokAI), u"https://api.x.ai/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::Qwen), u"https://dashscope-intl.aliyuncs.com/compatible-mode/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::NovitaAI), u"https://api.novita.ai/v3/openai/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::DeepInfra), u"https://api.deepinfra.com/v1/openai/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::ChatGPT), u"https://api.openai.com/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::CompactifAI), u"https://your-compactifai-api-endpoint/v1/"_s);
}

void GenericNetworkServerInfoTest::shouldChatCompletionPath()
{
    const GenericNetworkServerInfo info;
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::MistralAI), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::OpenAI), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::KlusterAI), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::GroqAI), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::CerebrasAI), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::VeniceAI), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::LlamaApi), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::Anthropic), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::KimiAI), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::GrokAI), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::Qwen), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::NovitaAI), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::DeepInfra), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::ChatGPT), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::CompactifAI), u"chat/completions"_s);
}

void GenericNetworkServerInfoTest::shouldDefinePluginName()
{
    const GenericNetworkServerInfo info;
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::MistralAI), u"mistralai"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::OpenAI), u"openai"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::KlusterAI), u"klusterai"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::GroqAI), u"groqai"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::CerebrasAI), u"cerebrasai"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::VeniceAI), u"veniceai"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::LlamaApi), u"llamaapi"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::Anthropic), u"anthropic"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::KimiAI), u"kimiai"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::GrokAI), u"grokai"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::Qwen), u"qwen"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::NovitaAI), u"novitaai"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::DeepInfra), u"deepinfra"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::ChatGPT), u"chatgpt"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::CompactifAI), u"compactifai"_s);
}

void GenericNetworkServerInfoTest::shouldDefineLimitations()
{
    const GenericNetworkServerInfo info;
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::MistralAI), GenericNetworkManager::Limitation::None);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::OpenAI), GenericNetworkManager::Limitation::None);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::KlusterAI), GenericNetworkManager::Limitation::None);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::GroqAI), GenericNetworkManager::Limitation::TextOnly);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::CerebrasAI), GenericNetworkManager::Limitation::None);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::LlamaApi), GenericNetworkManager::Limitation::None);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::Anthropic), GenericNetworkManager::Limitation::None);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::VeniceAI), GenericNetworkManager::Limitation::NoSystemMessage);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::KimiAI), GenericNetworkManager::Limitation::NoSeed);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::GrokAI), GenericNetworkManager::Limitation::None);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::Qwen), GenericNetworkManager::Limitation::None);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::NovitaAI), GenericNetworkManager::Limitation::NoSeed);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::DeepInfra), GenericNetworkManager::Limitation::None);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::ChatGPT), GenericNetworkManager::Limitation::UseMaxCompletionTokens);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::CompactifAI), GenericNetworkManager::Limitation::None);
}

#include "moc_genericnetworkserverinfotest.cpp"
