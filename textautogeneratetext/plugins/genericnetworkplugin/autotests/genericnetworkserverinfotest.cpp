/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkserverinfotest.h"
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
    QCOMPARE(info.pluginNetworkTypeFromString(QStringLiteral("mistralai")), GenericNetworkManager::PluginNetworkType::MistralAI);
    QCOMPARE(info.pluginNetworkTypeFromString(QStringLiteral("openai")), GenericNetworkManager::PluginNetworkType::OpenAI);
    QCOMPARE(info.pluginNetworkTypeFromString(QString()), GenericNetworkManager::PluginNetworkType::Unknown);
    QCOMPARE(info.pluginNetworkTypeFromString(QStringLiteral("openaisdfsdf")), GenericNetworkManager::PluginNetworkType::Unknown);
}

void GenericNetworkServerInfoTest::shouldCheckApiUrl()
{
    GenericNetworkServerInfo info;
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::MistralAI), QStringLiteral("https://chat.mistral.ai/"));
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::OpenAI), QStringLiteral("https://api.openai.com/v1/"));
    QCOMPARE(info.apiUrl(GenericNetworkManager::PluginNetworkType::KlusterAI), QStringLiteral("https://api.kluster.ai/v1/"));
}

#include "moc_genericnetworkserverinfotest.cpp"
