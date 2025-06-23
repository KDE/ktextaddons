/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerategenericnetwork_export.h"
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateManagerBase>
class GenericNetworkSettings;
class TEXTAUTOGENERATEGENERICNETWORK_EXPORT GenericNetworkManager : public TextAutoGenerateText::TextAutoGenerateManagerBase
{
    Q_OBJECT
public:
    enum class PluginNetworkType : uint8_t {
        Unknown = 0,
        MistralAI,
        OpenAI,
        KlusterAI,
        LastElement,
    };

    explicit GenericNetworkManager(GenericNetworkSettings *settings, QObject *parent = nullptr);
    ~GenericNetworkManager() override;

    void loadModels() override;

    [[nodiscard]] PluginNetworkType pluginNetworkType() const;
    void setPluginNetworkType(PluginNetworkType newPluginNetworkType);

    [[nodiscard]] QString translatedName() const;
    [[nodiscard]] QString webSite() const;

    [[nodiscard]] QString apiUrl() const;
    [[nodiscard]] QString description() const;

    [[nodiscard]] QString pluginName() const;

    [[nodiscard]] QString apiKey() const;
    void setApiKey(const QString &newApiKey);

    [[nodiscard]] QString translatedPluginName() const;

    [[nodiscard]] GenericNetworkSettings *genericNetworkSettings() const;

private:
    PluginNetworkType mPluginNetworkType = PluginNetworkType::Unknown;
    QString mApiKey;
    GenericNetworkSettings *const mGenericNetworkSettings;

    // TODO limitation type
};
