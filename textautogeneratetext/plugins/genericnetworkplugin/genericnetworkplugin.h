/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <TextAutoGenerateText/TextAutoGenerateTextPlugin>
class GenericNetworkSettings;
class GenericNetworkManager;
class GenericNetworkPlugin : public TextAutoGenerateText::TextAutoGenerateTextPlugin
{
    Q_OBJECT
public:
    explicit GenericNetworkPlugin(TextAutoGenerateText::TextAutoGenerateTextInstance *instance,
                                  TextAutoGenerateText::TextAutoGenerateManager *manager,
                                  QObject *parent = nullptr);
    ~GenericNetworkPlugin() override;

    [[nodiscard]] QString engineName() const override;
    [[nodiscard]] QString name() const;
    [[nodiscard]] QString translatedPluginName() const override;

    void showConfigureDialog(QWidget *parentWidget) override;

    void load(const KConfigGroup &config) override;
    void save(KConfigGroup &config) override;

    [[nodiscard]] QString displayName() const override;
    void setDisplayName(const QString &newName) override;

    [[nodiscard]] QString currentModel() const override;
    void setCurrentModel(const QString &) override;

    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType engineType() const override;

    void remove() override;

    [[nodiscard]] bool hasVisionSupport() const override;
    [[nodiscard]] bool hasToolsSupport() const override;
    [[nodiscard]] bool hasOcrSupport() const override;
    [[nodiscard]] bool hasAudioSupport() const override;

protected:
    void sendToAssistant(const SendToAssistantInfo &info) override;
    void askToAssistant(const QString &msg) override;
    void cancelRequest(const QByteArray &uuid) override;

Q_SIGNALS:
    void loadApiKeyDone();

private:
    void removeApiKey();
    void loadApiKey();
    GenericNetworkSettings *const mSettings;
    GenericNetworkManager *const mGenericManager;
};
