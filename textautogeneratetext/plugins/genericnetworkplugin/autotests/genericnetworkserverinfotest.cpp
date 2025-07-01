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
}

void GenericNetworkServerInfoTest::shouldCheckApiUrl()
{
    GenericNetworkServerInfo info;
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::MistralAI), u"https://api.mistral.ai/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::OpenAI), u"https://api.openai.com/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::KlusterAI), u"https://api.kluster.ai/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::GroqAI), u"https://api.groq.com/openai/v1/"_s);
}

void GenericNetworkServerInfoTest::shouldChatCompletionPath()
{
    GenericNetworkServerInfo info;
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::MistralAI), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::OpenAI), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::KlusterAI), u"chat/completions"_s);
    QCOMPARE(info.chatCompletionPath(GenericNetworkManager::PluginNetworkType::GroqAI), u"chat/completions"_s);
}

void GenericNetworkServerInfoTest::shouldDefinePluginName()
{
    GenericNetworkServerInfo info;
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::MistralAI), u"mistralai"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::OpenAI), u"openai"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::KlusterAI), u"klusterai"_s);
    QCOMPARE(info.pluginName(GenericNetworkManager::PluginNetworkType::GroqAI), u"groqai"_s);
}

#include "moc_genericnetworkserverinfotest.cpp"
