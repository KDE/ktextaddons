/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <TextAutoGenerateText/TextAutoGenerateTextClient>
class OllamaManager;
class OllamaClient : public TextAutoGenerateText::TextAutoGenerateTextClient
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.TextAutoGenerateText.ollama")
    Q_INTERFACES(TextAutoGenerateText::TextAutoGenerateTextClient)
public:
    explicit OllamaClient(QObject *parent = nullptr);
    ~OllamaClient() override;

    [[nodiscard]] QString name() const override;
    [[nodiscard]] QString translatedName() const override;
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateTextPlugin *createTextAutoGeneratePlugin() override;
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateTextClient::EngineType engineType() const override;
    [[nodiscard]] bool showConfigureDialog(QWidget *parentWidget) override;
    [[nodiscard]] QString modelName() const override;
    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer> supportedServers() const override;

private:
    OllamaManager *const mManager;
};
