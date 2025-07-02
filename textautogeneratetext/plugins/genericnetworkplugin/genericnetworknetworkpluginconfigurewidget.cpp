/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworknetworkpluginconfigurewidget.h"
#include "genericnetworkmanager.h"
#include "genericnetworksettings.h"

GenericNetworkNetworkPluginConfigureWidget::GenericNetworkNetworkPluginConfigureWidget(GenericNetworkManager *manager, QWidget *parent)
    : TextAutoGenerateText::TextAutoGenerateNetworkPluginConfigureWidget(parent)
    , mManager(manager)
{
    loadSettings();
    mManager->loadModels();
    setWebSiteUrl(mManager->webSite());
    setDescription(mManager->description());
}

GenericNetworkNetworkPluginConfigureWidget::~GenericNetworkNetworkPluginConfigureWidget() = default;

void GenericNetworkNetworkPluginConfigureWidget::loadSettings()
{
    setInstanceName(mManager->genericNetworkSettings()->displayName());
    setMaxTokens(mManager->genericNetworkSettings()->maxTokens());
    setTemperature(mManager->genericNetworkSettings()->temperature());
    setSeed(mManager->genericNetworkSettings()->seed());
    setApiKey(mManager->apiKey());
}

void GenericNetworkNetworkPluginConfigureWidget::saveSettings()
{
    mManager->genericNetworkSettings()->setDisplayName(instanceName());
    mManager->genericNetworkSettings()->setTemperature(temperature());
    mManager->genericNetworkSettings()->setMaxTokens(maxTokens());
    mManager->genericNetworkSettings()->setSeed(seed());
    mManager->setApiKey(apiKey());
}

#include "moc_genericnetworknetworkpluginconfigurewidget.cpp"
