/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworknetworkpluginconfigurewidget.h"
#include "genericnetworkmanager.h"
#include "genericnetworkserverinfo.h"
#include "genericnetworksettings.h"
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;

GenericNetworkNetworkPluginConfigureWidget::GenericNetworkNetworkPluginConfigureWidget(GenericNetworkManager *manager, QWidget *parent)
    : TextAutoGenerateText::TextAutoGenerateNetworkPluginConfigureWidget(parent)
    , mManager(manager)
{
    updateThinkingLevels();
    loadSettings();
    mManager->loadModels();
    setWebSiteUrl(mManager->webSite());
    setDescription(mManager->description());
    setHasCustomUrl(mManager->hasCustomUrl());
}

GenericNetworkNetworkPluginConfigureWidget::~GenericNetworkNetworkPluginConfigureWidget() = default;

void GenericNetworkNetworkPluginConfigureWidget::updateThinkingLevels()
{
    const QList<GenericNetworkServerInfo::ThinkingLevel> levels =
        GenericNetworkServerInfo::thinkingLevelList(mManager->pluginNetworkType(), mManager->genericNetworkSettings()->currentModel());
    QList<std::pair<QString, QString>> items;
    if (!levels.isEmpty()) {
        items.reserve(levels.count() + 1);
        // Empty value: don't send any level, the server uses its default
        items.append({QString(), i18nc("@item:inlistbox thinking level", "Default")});
        for (const auto level : levels) {
            items.append({GenericNetworkServerInfo::thinkingLevel(level), GenericNetworkServerInfo::thinkingLevelI18n(level)});
        }
    }
    setThinkingLevels(items);
}

void GenericNetworkNetworkPluginConfigureWidget::loadSettings()
{
    setInstanceName(mManager->genericNetworkSettings()->displayName());
    setMaxTokens(mManager->genericNetworkSettings()->maxTokens());
    setTemperature(mManager->genericNetworkSettings()->temperature());
    setSeed(mManager->genericNetworkSettings()->seed());
    setApiKey(mManager->apiKey());
    if (mManager->hasCustomUrl()) {
        setCustomUrl(mManager->genericNetworkSettings()->customUrl());
        setCustomModels(mManager->genericNetworkSettings()->customModels());
    }
    setThinkingLevel(mManager->genericNetworkSettings()->thinkingLevel());
}

void GenericNetworkNetworkPluginConfigureWidget::saveSettings()
{
    mManager->genericNetworkSettings()->setDisplayName(instanceName());
    mManager->genericNetworkSettings()->setTemperature(temperature());
    mManager->genericNetworkSettings()->setMaxTokens(maxTokens());
    mManager->genericNetworkSettings()->setSeed(seed());
    if (mManager->hasCustomUrl()) {
        mManager->genericNetworkSettings()->setCustomUrl(customUrl());
        mManager->genericNetworkSettings()->setCustomModels(customModels());
    }
    mManager->genericNetworkSettings()->setThinkingLevel(thinkingLevel());
    mManager->setApiKey(apiKey());
}

#include "moc_genericnetworknetworkpluginconfigurewidget.cpp"
