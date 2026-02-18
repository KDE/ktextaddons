/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "core/textautogeneratetextplugin.h"

class OllamaOnlineSettings;
class OllamaOnlineManager;
class OllamaOnlinePlugin : public TextAutoGenerateText::TextAutoGenerateTextPlugin
{
    Q_OBJECT
public:
    explicit OllamaOnlinePlugin(TextAutoGenerateText::TextAutoGenerateManager *manager,
                                TextAutoGenerateText::TextAutoGenerateTextInstance *instance,
                                QObject *parent = nullptr);
    ~OllamaOnlinePlugin() override;

    [[nodiscard]] QString engineName() const override;

    [[nodiscard]] QString translatedPluginName() const override;

    void showConfigureDialog(QWidget *parentWidget) override;

    void load(const KConfigGroup &config) override;
    void save(KConfigGroup &config) override;

    [[nodiscard]] QString displayName() const override;
    void setDisplayName(const QString &newName) override;
    [[nodiscard]] QString currentModel() const override;
    void setCurrentModel(const QString &) override;

    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType engineType() const override;

    [[nodiscard]] bool hasVisionSupport() const override;
    [[nodiscard]] bool hasToolsSupport() const override;
    [[nodiscard]] bool hasOcrSupport() const override;
    [[nodiscard]] bool hasAudioSupport() const override;

    void remove() override;
    [[nodiscard]] QString passwordServiceName() const;
    [[nodiscard]] QString shareNamePrompt() const override;
Q_SIGNALS:
    void loadApiKeyDone();

protected:
    void sendToAssistant(const SendToAssistantInfo &info) override;
    void askToAssistant(const QString &msg) override;

private:
    void removeApiKey();
    void loadApiKey();
    OllamaOnlineSettings *const mOllamaOnlineSettings;
    OllamaOnlineManager *const mOllamaOnlineManager;
};
