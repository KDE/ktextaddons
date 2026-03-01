/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "genericnetworkmanager.h"
#include "textautogenerategenericnetwork_export.h"
#include <QString>
#include <TextAutoGenerateText/TextAutoGenerateTextClient>

class TEXTAUTOGENERATEGENERICNETWORK_EXPORT GenericNetworkServerInfo
{
    Q_GADGET
public:
    GenericNetworkServerInfo();
    ~GenericNetworkServerInfo();
    [[nodiscard]] static QString translatedName(GenericNetworkManager::PluginNetworkType type);
    [[nodiscard]] static QString webSite(GenericNetworkManager::PluginNetworkType type);

    [[nodiscard]] static QString apiUrl(GenericNetworkManager::PluginNetworkType type);
    [[nodiscard]] static QString description(GenericNetworkManager::PluginNetworkType type);

    [[nodiscard]] static QString pluginName(GenericNetworkManager::PluginNetworkType type);
    [[nodiscard]] static QList<TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer> supportedServers(const QString &pluginName);
    [[nodiscard]] static GenericNetworkManager::PluginNetworkType pluginNetworkTypeFromString(const QString &str);

    [[nodiscard]] static GenericNetworkManager::Limitations limitations(GenericNetworkManager::PluginNetworkType type);
    [[nodiscard]] static QString chatCompletionPath(GenericNetworkManager::PluginNetworkType type);
    [[nodiscard]] static bool hasVisionSupport(const QString &currentModel, GenericNetworkManager::PluginNetworkType type);
    [[nodiscard]] static bool hasToolsSupport(const QString &currentMode, GenericNetworkManager::PluginNetworkType type);
    [[nodiscard]] static bool hasOcrSupport(const QString &currentModel, GenericNetworkManager::PluginNetworkType type);
    [[nodiscard]] static bool hasAudioSupport(const QString &currentMode, GenericNetworkManager::PluginNetworkType type);
    [[nodiscard]] static bool hasThinkSupport(const QString &currentMode, GenericNetworkManager::PluginNetworkType type);
};
