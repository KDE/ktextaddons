/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <TextAutogenerateText/TextAutogenerateTextClient>

class OllamaClient : public TextAutogenerateText::TextAutogenerateTextClient
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.TextAutogenerateText.ollama")
    Q_INTERFACES(TextAutogenerateText::TextAutogenerateTextClient)
public:
    explicit OllamaClient(QObject *parent = nullptr);
    ~OllamaClient() override;

    [[nodiscard]] QString name() const override;
    [[nodiscard]] QString translatedName() const override;
    [[nodiscard]] TextAutogenerateText::TextAutogenerateTextPlugin *createTextAutogeneratePlugin() override;
    [[nodiscard]] TextAutogenerateText::TextAutogenerateTextClient::EngineType engineType() const override;
    [[nodiscard]] bool hasConfigurationDialog() const override;
    [[nodiscard]] bool showConfigureDialog(QWidget *parentWidget) override;
    [[nodiscard]] QString webSite() const override;
    [[nodiscard]] QString modelName() const override;
};
