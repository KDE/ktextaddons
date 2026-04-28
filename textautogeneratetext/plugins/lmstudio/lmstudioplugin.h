/*
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "core/textautogeneratetextplugin.h"

class LMStudioManager;
class LMStudioSettings;
class LMStudioPlugin : public TextAutoGenerateText::TextAutoGenerateTextPlugin
{
    Q_OBJECT
public:
    explicit LMStudioPlugin(TextAutoGenerateText::TextAutoGenerateManager *manager,
                            TextAutoGenerateText::TextAutoGenerateTextInstance *instance,
                            QObject *parent = nullptr);
    ~LMStudioPlugin() override;

    [[nodiscard]] QString engineName() const override;

    [[nodiscard]] QString translatedPluginName() const override;

    void showConfigureDialog(QWidget *parentWidget) override;

    void load(const KConfigGroup &config) override;
    void save(KConfigGroup &config) override;
    void remove() override;

    [[nodiscard]] QString displayName() const override;
    void setDisplayName(const QString &newName) override;
    [[nodiscard]] QString currentModel() const override;
    void setCurrentModel(const QString &) override;

    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType engineType() const override;

    [[nodiscard]] bool hasVisionSupport() const override;
    [[nodiscard]] bool hasToolsSupport() const override;
    [[nodiscard]] bool hasOcrSupport() const override;
    [[nodiscard]] bool hasAudioSupport() const override;
    [[nodiscard]] bool hasThinkSupport() const override;
    [[nodiscard]] QString shareNamePrompt() const override;

    [[nodiscard]] QString passwordServiceName() const;

protected:
    void sendToAssistant(const SendToAssistantInfo &info) override;
    void askToAssistant(const QString &msg) override;

Q_SIGNALS:
    void loadApiKeyDone();

private:
    void removeApiKey();
    void loadApiKey();
    void slotLMStudioRequested();
    void slotLMStudioFailed(const QString &errorStr);
    void slotLMStudioStarted();
    LMStudioSettings *const mLMStudioSettings;
    LMStudioManager *const mLMStudioManager;
};
