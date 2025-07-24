/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

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
    GenericNetworkServerInfo info;
    QCOMPARE(info.pluginNetworkTypeFromString(u"mistralai"_s), GenericNetworkManager::PluginNetworkType::MistralAI);
    QCOMPARE(info.pluginNetworkTypeFromString(u"openai"_s), GenericNetworkManager::PluginNetworkType::OpenAI);
    QCOMPARE(info.pluginNetworkTypeFromString(QString()), GenericNetworkManager::PluginNetworkType::Unknown);
    QCOMPARE(info.pluginNetworkTypeFromString(u"openaisdfsdf"_s), GenericNetworkManager::PluginNetworkType::Unknown);
    QCOMPARE(info.pluginNetworkTypeFromString(u"groqai"_s), GenericNetworkManager::PluginNetworkType::GroqAI);
    QCOMPARE(info.pluginNetworkTypeFromString(u"cerebrasai"_s), GenericNetworkManager::PluginNetworkType::CerebrasAI);
    QCOMPARE(info.pluginNetworkTypeFromString(u"veniceai"_s), GenericNetworkManager::PluginNetworkType::VeniceAI);
    QCOMPARE(info.pluginNetworkTypeFromString(u"llamaapi"_s), GenericNetworkManager::PluginNetworkType::LlamaApi);
}

void GenericNetworkServerInfoTest::shouldCheckApiUrl()
{
    GenericNetworkServerInfo info;
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::MistralAI), u"https://api.mistral.ai/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::OpenAI), u"https://api.openai.com/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::KlusterAI), u"https://api.kluster.ai/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::GroqAI), u"https://api.groq.com/openai/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::CerebrasAI), u"https://api.cerebras.ai/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::VeniceAI), u"https://api.venice.ai/api/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::LlamaApi), u"https://api.llama.com/compat/v1/"_s);
}

void GenericNetworkServerInfoTest::shouldChatCompletionPath()
{
    GenericNetworkServerInfo info;
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::MistralAI), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::OpenAI), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::KlusterAI), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::GroqAI), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::CerebrasAI), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::VeniceAI), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::LlamaApi), u"chat/completions"_s);
}

void GenericNetworkServerInfoTest::shouldDefinePluginName()
{
    GenericNetworkServerInfo info;
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::MistralAI), u"mistralai"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::OpenAI), u"openai"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::KlusterAI), u"klusterai"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::GroqAI), u"groqai"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::CerebrasAI), u"cerebrasai"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::VeniceAI), u"veniceai"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::LlamaApi), u"llamaapi"_s);
}

void GenericNetworkServerInfoTest::shouldDefineLimitations()
{
    GenericNetworkServerInfo info;
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::MistralAI), GenericNetworkServerInfo::Limitation::None);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::OpenAI), GenericNetworkServerInfo::Limitation::None);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::KlusterAI), GenericNetworkServerInfo::Limitation::None);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::GroqAI), GenericNetworkServerInfo::Limitation::TextOnly);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::CerebrasAI), GenericNetworkServerInfo::Limitation::None);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::LlamaApi), GenericNetworkServerInfo::Limitation::None);
    QCOMPARE(info.limitations(GenericNetworkManager::PluginNetworkType::VeniceAI), GenericNetworkServerInfo::Limitation::NoSystemMessage);
}

#include "moc_genericnetworkserverinfotest.cpp"
