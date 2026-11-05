/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "genericnetworkmanager.h"
#include "textautogenerategenericnetwork_export.h"
#include <QList>
#include <QString>
#include <TextAutoGenerateText/TextAutoGenerateTextClient>
class QJsonObject;

class TEXTAUTOGENERATEGENERICNETWORK_EXPORT GenericNetworkServerInfo
{
    Q_GADGET
public:
    enum class ThinkingLevel : uint8_t {
        Unknown = 0,
        Disabled,
        Enabled,
        Minimal,
        Low,
        Medium,
        High,
        Xhigh,
    };
    Q_ENUM(ThinkingLevel)

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
    [[nodiscard]] static QString responsesPath(GenericNetworkManager::PluginNetworkType type);
    [[nodiscard]] static bool hasCustomUrl(GenericNetworkManager::PluginNetworkType type);
    [[nodiscard]] static QList<GenericNetworkModelAvailableInfo> defaultModels(GenericNetworkManager::PluginNetworkType type);
    [[nodiscard]] static bool modelSupportsTools(GenericNetworkManager::PluginNetworkType type, const QString &identifier);
    [[nodiscard]] static QString thinkingLevelI18n(ThinkingLevel level);
    [[nodiscard]] static QString thinkingLevel(ThinkingLevel level);

    [[nodiscard]] static QList<ThinkingLevel> thinkingLevelList(GenericNetworkManager::PluginNetworkType type, const QString &identifier);
    [[nodiscard]] static bool isThinkingLevelSupported(GenericNetworkManager::PluginNetworkType type, const QString &identifier, const QString &level);
    static void thinkingJson(QJsonObject &data,
                             const QString &level,
                             GenericNetworkManager::PluginNetworkType type,
                             GenericNetworkManager::ApiType api = GenericNetworkManager::ApiType::ChatCompletions);
};
