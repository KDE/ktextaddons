/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "core/textautogeneratetextplugin.h"

#include <QMultiHash>
#include <QPair>
class OllamaManager;
class OllamaSettings;
class OllamaPlugin : public TextAutoGenerateText::TextAutoGenerateTextPlugin
{
    Q_OBJECT
public:
    explicit OllamaPlugin(TextAutoGenerateText::TextAutoGenerateManager *manager,
                          TextAutoGenerateText::TextAutoGenerateTextInstance *instance,
                          QObject *parent = nullptr);
    ~OllamaPlugin() override;

    void setPrompt(const QString &text) override;

    [[nodiscard]] QString engineName() const override;

    [[nodiscard]] QString translatedPluginName() const override;

    void showConfigureDialog(QWidget *parentWidget) override;

    void load(const KConfigGroup &config) override;
    void save(KConfigGroup &config) override;

    [[nodiscard]] QString displayName() const override;
    void setDisplayName(const QString &newName) override;
    [[nodiscard]] QString currentModel() const override;
    void setCurrentModel(const QString &) override;

protected:
    void sendToAssistant(const SendToAssistantInfo &info) override;
    void askToAssistant(const QString &msg) override;

private:
    OllamaSettings *const mOllamaSettings;
    OllamaManager *const mManager;
};
