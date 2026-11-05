/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkserverinfotest.h"

#include "genericnetworkserverinfo.h"
#include <QStandardPaths>
#include <QTest>

#include <algorithm>
QTEST_GUILESS_MAIN(GenericNetworkServerInfoTest)

using namespace Qt::Literals::StringLiterals;
GenericNetworkServerInfoTest::GenericNetworkServerInfoTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
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
    QCOMPARE(info.pluginNetworkTypeFromString(u"openrouterai"_s), GenericNetworkManager::PluginNetworkType::OpenRouterAI);
    QCOMPARE(info.pluginNetworkTypeFromString(u"sarvamai"_s), GenericNetworkManager::PluginNetworkType::SarvamAI);
    QCOMPARE(info.pluginNetworkTypeFromString(u"atlascloudai"_s), GenericNetworkManager::PluginNetworkType::AtlasCloud);
    QCOMPARE(info.pluginNetworkTypeFromString(u"gemini"_s), GenericNetworkManager::PluginNetworkType::Gemini);
    QCOMPARE(info.pluginNetworkTypeFromString(u"orcarouterai"_s), GenericNetworkManager::PluginNetworkType::OrcaRouterAI);
    QCOMPARE(info.pluginNetworkTypeFromString(u"openaigeneric"_s), GenericNetworkManager::PluginNetworkType::OpenAIGeneric);
    QCOMPARE(info.pluginNetworkTypeFromString(u"deepseek"_s), GenericNetworkManager::PluginNetworkType::DeepSeek);
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
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::CompactifAI), u"https://api.compactif.ai/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::OpenRouterAI), u"https://openrouter.ai/api/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::SarvamAI), u"https://api.sarvam.ai/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::AtlasCloud), u"https://api.atlascloud.ai/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::OrcaRouterAI), u"https://api.orcarouter.ai/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::Gemini), u"https://generativelanguage.googleapis.com/v1beta/openai/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::OpenAIGeneric), QString());
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::DeepSeek), u"https://api.deepseek.com/v1/"_s);
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
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::OpenRouterAI), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::SarvamAI), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::AtlasCloud), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::Gemini), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::OrcaRouterAI), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::OpenRouterAI), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::DeepSeek), u"chat/completions"_s);
}

void GenericNetworkServerInfoTest::shouldResponsesPath()
{
    const GenericNetworkServerInfo info;
    QCOMPARE(info.responsesPath(GenericNetworkManager::PluginNetworkType::MistralAI), u"responses"_s);
    QCOMPARE(info.responsesPath(GenericNetworkManager::PluginNetworkType::OpenAI), u"responses"_s);
    QCOMPARE(info.responsesPath(GenericNetworkManager::PluginNetworkType::KlusterAI), u"responses"_s);
    QCOMPARE(info.responsesPath(GenericNetworkManager::PluginNetworkType::GroqAI), u"responses"_s);
    QCOMPARE(info.responsesPath(GenericNetworkManager::PluginNetworkType::CerebrasAI), u"responses"_s);
    QCOMPARE(info.responsesPath(GenericNetworkManager::PluginNetworkType::VeniceAI), u"responses"_s);
    QCOMPARE(info.responsesPath(GenericNetworkManager::PluginNetworkType::LlamaApi), u"responses"_s);
    QCOMPARE(info.responsesPath(GenericNetworkManager::PluginNetworkType::Anthropic), u"responses"_s);
    QCOMPARE(info.responsesPath(GenericNetworkManager::PluginNetworkType::KimiAI), u"responses"_s);
    QCOMPARE(info.responsesPath(GenericNetworkManager::PluginNetworkType::GrokAI), u"responses"_s);
    QCOMPARE(info.responsesPath(GenericNetworkManager::PluginNetworkType::Qwen), u"responses"_s);
    QCOMPARE(info.responsesPath(GenericNetworkManager::PluginNetworkType::NovitaAI), u"responses"_s);
    QCOMPARE(info.responsesPath(GenericNetworkManager::PluginNetworkType::DeepInfra), u"responses"_s);
    QCOMPARE(info.responsesPath(GenericNetworkManager::PluginNetworkType::ChatGPT), u"responses"_s);
    QCOMPARE(info.responsesPath(GenericNetworkManager::PluginNetworkType::CompactifAI), u"responses"_s);
    QCOMPARE(info.responsesPath(GenericNetworkManager::PluginNetworkType::OpenRouterAI), u"responses"_s);
    QCOMPARE(info.responsesPath(GenericNetworkManager::PluginNetworkType::SarvamAI), u"responses"_s);
    QCOMPARE(info.responsesPath(GenericNetworkManager::PluginNetworkType::AtlasCloud), u"responses"_s);
    QCOMPARE(info.responsesPath(GenericNetworkManager::PluginNetworkType::Gemini), u"responses"_s);
    QCOMPARE(info.responsesPath(GenericNetworkManager::PluginNetworkType::OrcaRouterAI), u"responses"_s);
    QCOMPARE(info.responsesPath(GenericNetworkManager::PluginNetworkType::OpenAIGeneric), u"responses"_s);
    QCOMPARE(info.responsesPath(GenericNetworkManager::PluginNetworkType::DeepSeek), u"responses"_s);
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
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::OpenRouterAI), u"openrouterai"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::SarvamAI), u"sarvamai"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::AtlasCloud), u"atlascloudai"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::Gemini), u"gemini"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::OrcaRouterAI), u"orcarouterai"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::OpenAIGeneric), u"openaigeneric"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::DeepSeek), u"deepseek"_s);
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
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::OpenRouterAI), GenericNetworkManager::Limitation::None);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::SarvamAI), GenericNetworkManager::Limitation::None);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::AtlasCloud), GenericNetworkManager::Limitation::None);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::Gemini), GenericNetworkManager::Limitation::None);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::OrcaRouterAI), GenericNetworkManager::Limitation::None);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::OpenAIGeneric), GenericNetworkManager::Limitation::None);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::DeepSeek), GenericNetworkManager::Limitation::NoSeed);
}

void GenericNetworkServerInfoTest::shouldDefineDefaultModels()
{
    const GenericNetworkServerInfo info;
    QVERIFY(info.defaultModels(GenericNetworkManager::PluginNetworkType::Unknown).isEmpty());
    QVERIFY(info.defaultModels(GenericNetworkManager::PluginNetworkType::MistralAI).isEmpty());
    QVERIFY(info.defaultModels(GenericNetworkManager::PluginNetworkType::OpenAI).isEmpty());
    QVERIFY(info.defaultModels(GenericNetworkManager::PluginNetworkType::OpenAIGeneric).isEmpty());
    QVERIFY(info.defaultModels(GenericNetworkManager::PluginNetworkType::DeepSeek).isEmpty());
}

void GenericNetworkServerInfoTest::shouldConvertThinkingLevel()
{
    using Level = GenericNetworkServerInfo::ThinkingLevel;
    QVERIFY(GenericNetworkServerInfo::thinkingLevel(Level::Unknown).isEmpty());
    QCOMPARE(GenericNetworkServerInfo::thinkingLevel(Level::Disabled), u"none"_s);
    QCOMPARE(GenericNetworkServerInfo::thinkingLevel(Level::Enabled), u"enabled"_s);
    QCOMPARE(GenericNetworkServerInfo::thinkingLevel(Level::Minimal), u"minimal"_s);
    QCOMPARE(GenericNetworkServerInfo::thinkingLevel(Level::Low), u"low"_s);
    QCOMPARE(GenericNetworkServerInfo::thinkingLevel(Level::Medium), u"medium"_s);
    QCOMPARE(GenericNetworkServerInfo::thinkingLevel(Level::High), u"high"_s);
    QCOMPARE(GenericNetworkServerInfo::thinkingLevel(Level::Xhigh), u"xhigh"_s);
}

void GenericNetworkServerInfoTest::shouldTranslateThinkingLevel()
{
    using Level = GenericNetworkServerInfo::ThinkingLevel;
    QVERIFY(GenericNetworkServerInfo::thinkingLevelI18n(Level::Unknown).isEmpty());
    const QList<Level> levels{Level::Disabled, Level::Enabled, Level::Minimal, Level::Low, Level::Medium, Level::High, Level::Xhigh};
    QStringList labels;
    for (const auto level : levels) {
        const QString label = GenericNetworkServerInfo::thinkingLevelI18n(level);
        QVERIFY(!label.isEmpty());
        QVERIFY(!labels.contains(label));
        labels.append(label);
    }
}

void GenericNetworkServerInfoTest::shouldOrderThinkingLevel()
{
    using Level = GenericNetworkServerInfo::ThinkingLevel;
    QVERIFY(Level::Disabled < Level::Enabled);
    QVERIFY(Level::Enabled < Level::Minimal);
    QVERIFY(Level::Minimal < Level::Low);
    QVERIFY(Level::Low < Level::Medium);
    QVERIFY(Level::Medium < Level::High);
    QVERIFY(Level::High < Level::Xhigh);
}

void GenericNetworkServerInfoTest::shouldDefineThinkingLevelList()
{
    using Level = GenericNetworkServerInfo::ThinkingLevel;
    using Type = GenericNetworkManager::PluginNetworkType;
    const GenericNetworkServerInfo info;

    // OpenAI
    QVERIFY(info.thinkingLevelList(Type::OpenAI, u"gpt-4o"_s).isEmpty());
    QVERIFY(info.thinkingLevelList(Type::OpenAI, u"gpt-4.1-mini"_s).isEmpty());
    QVERIFY(info.thinkingLevelList(Type::OpenAI, u"gpt-5-chat-latest"_s).isEmpty());
    QCOMPARE(info.thinkingLevelList(Type::OpenAI, u"o3-mini"_s), (QList<Level>{Level::Low, Level::Medium, Level::High}));
    QCOMPARE(info.thinkingLevelList(Type::OpenAI, u"o4-mini"_s), (QList<Level>{Level::Low, Level::Medium, Level::High}));
    QCOMPARE(info.thinkingLevelList(Type::OpenAI, u"gpt-5"_s), (QList<Level>{Level::Minimal, Level::Low, Level::Medium, Level::High}));
    QCOMPARE(info.thinkingLevelList(Type::OpenAI, u"gpt-5-mini"_s), (QList<Level>{Level::Minimal, Level::Low, Level::Medium, Level::High}));
    QCOMPARE(info.thinkingLevelList(Type::OpenAI, u"gpt-5-pro"_s), (QList<Level>{Level::High}));
    QCOMPARE(info.thinkingLevelList(Type::OpenAI, u"gpt-5.1"_s), (QList<Level>{Level::Disabled, Level::Low, Level::Medium, Level::High}));
    QCOMPARE(info.thinkingLevelList(Type::OpenAI, u"gpt-5.2"_s), (QList<Level>{Level::Disabled, Level::Low, Level::Medium, Level::High, Level::Xhigh}));
    QCOMPARE(info.thinkingLevelList(Type::ChatGPT, u"gpt-5.2"_s), info.thinkingLevelList(Type::OpenAI, u"gpt-5.2"_s));

    // Gemini
    QVERIFY(info.thinkingLevelList(Type::Gemini, u"models/gemini-2.0-flash"_s).isEmpty());
    QCOMPARE(info.thinkingLevelList(Type::Gemini, u"models/gemini-2.5-pro"_s), (QList<Level>{Level::Low, Level::Medium, Level::High}));
    QCOMPARE(info.thinkingLevelList(Type::Gemini, u"models/gemini-2.5-flash"_s), (QList<Level>{Level::Disabled, Level::Low, Level::Medium, Level::High}));
    QCOMPARE(info.thinkingLevelList(Type::Gemini, u"models/gemini-3-pro-preview"_s), (QList<Level>{Level::Low, Level::High}));
    QCOMPARE(info.thinkingLevelList(Type::Gemini, u"models/gemini-3-flash-preview"_s), (QList<Level>{Level::Minimal, Level::Low, Level::Medium, Level::High}));

    // Grok
    QCOMPARE(info.thinkingLevelList(Type::GrokAI, u"grok-3-mini"_s), (QList<Level>{Level::Low, Level::High}));
    QVERIFY(info.thinkingLevelList(Type::GrokAI, u"grok-4"_s).isEmpty());

    QCOMPARE(info.thinkingLevelList(Type::OpenAIGeneric, u"foo"_s), (QList<Level>{Level::Low, Level::Medium, Level::High}));

    // Thinking can only be switched on or off
    const QList<Level> onOff{Level::Disabled, Level::Enabled};
    QCOMPARE(info.thinkingLevelList(Type::Anthropic, u"claude-sonnet-4-5"_s), onOff);
    QCOMPARE(info.thinkingLevelList(Type::Anthropic, u"claude-3-7-sonnet-latest"_s), onOff);
    QVERIFY(info.thinkingLevelList(Type::Anthropic, u"claude-3-5-haiku-latest"_s).isEmpty());
    QCOMPARE(info.thinkingLevelList(Type::DeepSeek, u"deepseek-chat"_s), onOff);
    QCOMPARE(info.thinkingLevelList(Type::Qwen, u"qwen3-max"_s), onOff);
    QVERIFY(info.thinkingLevelList(Type::MistralAI, u"magistral-medium-latest"_s).isEmpty());

    // Levels must be sorted
    const QStringList identifiers{u"gpt-5"_s, u"gpt-5.2"_s, u"o3"_s, u"gemini-2.5-flash"_s, u"gemini-3-pro"_s, u"grok-3-mini"_s, u"foo"_s};
    for (int i = 1; i <= static_cast<int>(Type::LastElement); ++i) {
        const auto type = static_cast<Type>(i);
        for (const auto &identifier : identifiers) {
            const QList<Level> levels = info.thinkingLevelList(type, identifier);
            QVERIFY(std::is_sorted(levels.cbegin(), levels.cend()));
            QVERIFY(!levels.contains(Level::Unknown));
        }
    }
}

void GenericNetworkServerInfoTest::shouldDefineModelSupportsTools()
{
    const GenericNetworkServerInfo info;
    QVERIFY(!info.modelSupportsTools(GenericNetworkManager::PluginNetworkType::Unknown, u"foo"_s));
    QVERIFY(info.modelSupportsTools(GenericNetworkManager::PluginNetworkType::Anthropic, u"claude-opus-4-8"_s));
    QVERIFY(info.modelSupportsTools(GenericNetworkManager::PluginNetworkType::Gemini, u"models/gemini-2.5-flash"_s));
    QVERIFY(!info.modelSupportsTools(GenericNetworkManager::PluginNetworkType::Gemini, u"models/gemini-embedding-001"_s));
    QVERIFY(!info.modelSupportsTools(GenericNetworkManager::PluginNetworkType::Gemini, u"models/gemini-2.5-flash-preview-tts"_s));
    QVERIFY(!info.modelSupportsTools(GenericNetworkManager::PluginNetworkType::Gemini, u"models/gemini-2.5-flash-image"_s));
    QVERIFY(!info.modelSupportsTools(GenericNetworkManager::PluginNetworkType::Gemini, u"models/imagen-4.0-generate-001"_s));
    QVERIFY(!info.modelSupportsTools(GenericNetworkManager::PluginNetworkType::Gemini, u"models/gemma-3-27b-it"_s));
    QVERIFY(!info.modelSupportsTools(GenericNetworkManager::PluginNetworkType::MistralAI, u"mistral-large-latest"_s));
    QVERIFY(!info.modelSupportsTools(GenericNetworkManager::PluginNetworkType::OpenAI, u"gpt-4o"_s));
    QVERIFY(info.modelSupportsTools(GenericNetworkManager::PluginNetworkType::DeepSeek, u"deepseek-flash"_s));
    QVERIFY(info.modelSupportsTools(GenericNetworkManager::PluginNetworkType::DeepSeek, u"deepseek-v4-pro"_s));
}

void GenericNetworkServerInfoTest::shouldContainDeepSeekInSupportedServers()
{
    const GenericNetworkServerInfo info;
    const auto servers = info.supportedServers(u"generic"_s);
    const auto it = std::find_if(servers.cbegin(), servers.cend(), [](const auto &server) {
        return server.identifier == u"deepseek"_s;
    });
    QVERIFY(it != servers.cend());
    QCOMPARE(it->pluginName, u"generic"_s);
}

#include "moc_genericnetworkserverinfotest.cpp"
