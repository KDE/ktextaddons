/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "genericnetworkmanager.h"
#include "textautogenerategenericnetwork_export.h"
#include <QString>
#include <TextAutoGenerateText/TextAutoGenerateTextClient>

class TEXTAUTOGENERATEGENERICNETWORK_EXPORT GenericNetworkServerInfo
{
public:
    enum Limitation : uint8_t {
        None = 0,
        TextOnly = 1,
        NoSeed = 2,
        NoSystemMessage = 4,
    };
    Q_FLAGS(Limitation Limitations)
    Q_DECLARE_FLAGS(Limitations, Limitation)

    GenericNetworkServerInfo();
    ~GenericNetworkServerInfo();
    [[nodiscard]] QString translatedName(GenericNetworkManager::PluginNetworkType type) const;
    [[nodiscard]] QString webSite(GenericNetworkManager::PluginNetworkType type) const;

    [[nodiscard]] QString apiUrl(GenericNetworkManager::PluginNetworkType type) const;
    [[nodiscard]] QString description(GenericNetworkManager::PluginNetworkType type) const;

    [[nodiscard]] QString pluginName(GenericNetworkManager::PluginNetworkType type) const;
    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer> supportedServers(const QString &pluginName) const;
    [[nodiscard]] GenericNetworkManager::PluginNetworkType pluginNetworkTypeFromString(const QString &str) const;

    [[nodiscard]] Limitations limitations(GenericNetworkManager::PluginNetworkType type) const;
    [[nodiscard]] QString chatCompletionPath(GenericNetworkManager::PluginNetworkType type) const;
    [[nodiscard]] bool hasVisionSupport(const QString &currentModel, GenericNetworkManager::PluginNetworkType type) const;
    [[nodiscard]] bool hasToolsSupport(const QString &currentMode, GenericNetworkManager::PluginNetworkType type) const;
};
