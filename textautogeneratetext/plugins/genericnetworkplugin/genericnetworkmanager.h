/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

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
        MistralAI,
        OpenAI,
        KlusterAI,
        GroqAI,
        CerebrasAI,
        VeniceAI,
        LlamaApi,
        Anthropic,
        LastElement,
    };

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

private:
    [[nodiscard]] TEXTAUTOGENERATEGENERICNETWORK_NO_EXPORT QString chatPath() const;
    PluginNetworkType mPluginNetworkType = PluginNetworkType::Unknown;
    QString mApiKey;
    GenericNetworkSettings *const mGenericNetworkSettings;
    GenericNetworkServerInfo *const mServerInfo;

    QList<GenericNetworkModelAvailableInfo> mInfos;
};
