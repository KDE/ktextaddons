/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkserverinfotest.h"
using namespace Qt::Literals::StringLiterals;

#include "genericnetworkserverinfo.h"
#include <QTest>
QTEST_GUILESS_MAIN(GenericNetworkServerInfoTest)

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
}

void GenericNetworkServerInfoTest::shouldCheckApiUrl()
{
    GenericNetworkServerInfo info;
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::MistralAI), u"https://chat.mistral.ai/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::OpenAI), u"https://api.openai.com/v1/"_s);
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::KlusterAI), u"https://api.kluster.ai/v1/"_s);
}

#include "moc_genericnetworkserverinfotest.cpp"
