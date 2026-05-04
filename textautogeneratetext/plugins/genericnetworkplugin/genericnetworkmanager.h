/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "modelsmanager/genericnetworkmodelavailableinfo.h"
#include "textautogenerategenericnetwork_export.h"
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateManagerBase>
class GenericNetworkSettings;
class GenericNetworkServerInfo;
class TEXTAUTOGENERATEGENERICNETWORK_EXPORT GenericNetworkManager : public TextAutoGenerateText::TextAutoGenerateManagerBase
{
    Q_OBJECT
public:
    enum class PluginNetworkType : uint8_t {
        Unknown = 0,
        CompactifAI = 1,
        NovitaAI = 2,
        DeepInfra = 3,
        MistralAI = 4,
        OpenAI = 5,
        KlusterAI = 6,
        GroqAI = 7,
        CerebrasAI = 8,
        VeniceAI = 9,
        LlamaApi = 10,
        Anthropic = 11,
        GrokAI = 12,
        Qwen = 13,
        ChatGPT = 14,
        OpenRouterAI = 15,
        SarvamAI = 16,
        AtlasCloud = 17,
        KimiAI = 18,
        LastElement = KimiAI,
    };

    enum Limitation : uint8_t {
        None = 0,
        TextOnly = 1,
        NoSeed = 2,
        NoSystemMessage = 4,
        UseMaxCompletionTokens = 8,
    };
    Q_DECLARE_FLAGS(Limitations, Limitation)
    Q_FLAG(Limitations)

    explicit GenericNetworkManager(GenericNetworkSettings *settings, QObject *parent = nullptr);
    ~GenericNetworkManager() override;

    void loadModels() override;
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateReply *getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request) override;
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateReply *getCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request) override;

    [[nodiscard]] PluginNetworkType pluginNetworkType() const;
    void setPluginNetworkType(PluginNetworkType newPluginNetworkType);

    [[nodiscard]] QString webSite() const;

    [[nodiscard]] QString apiUrl() const;
    [[nodiscard]] QString description() const;

    [[nodiscard]] QString pluginName() const;

    [[nodiscard]] QString apiKey() const;
    void setApiKey(const QString &newApiKey);

    [[nodiscard]] QString translatedPluginName() const;

    [[nodiscard]] GenericNetworkSettings *genericNetworkSettings() const;

    [[nodiscard]] QList<GenericNetworkModelAvailableInfo> infos() const;
    void setInfos(const QList<GenericNetworkModelAvailableInfo> &newInfos);

    [[nodiscard]] bool hasVisionSupport(const QString &currentModel) const;
    [[nodiscard]] bool hasToolsSupport(const QString &currentModel) const;
    [[nodiscard]] bool hasOcrSupport(const QString &currentModel) const;
    [[nodiscard]] bool hasAudioSupport(const QString &currentModel) const;
    [[nodiscard]] bool hasThinkSupport(const QString &currentModel) const;
    [[nodiscard]] GenericNetworkManager::Limitations limitations(GenericNetworkManager::PluginNetworkType type) const;
    [[nodiscard]] bool hasSystemMessageSupport() const;
    [[nodiscard]] bool hasTextOnlySupport() const;

private:
    [[nodiscard]] TEXTAUTOGENERATEGENERICNETWORK_NO_EXPORT QString chatPath() const;
    PluginNetworkType mPluginNetworkType = PluginNetworkType::Unknown;
    QString mApiKey;
    GenericNetworkSettings *const mGenericNetworkSettings;
    GenericNetworkServerInfo *const mServerInfo;

    QList<GenericNetworkModelAvailableInfo> mInfos;
};
