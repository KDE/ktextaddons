/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <TextAutogenerateText/TextAutogenerateTextClient>

class MistralClient : public TextAutogenerateText::TextAutoGenerateTextClient
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.TextAutogenerateText.mistral")
    Q_INTERFACES(TextAutogenerateText::TextAutoGenerateTextClient)
public:
    explicit MistralClient(QObject *parent = nullptr);
    ~MistralClient() override;

    [[nodiscard]] QString name() const override;
    [[nodiscard]] QString translatedName() const override;
    [[nodiscard]] TextAutogenerateText::TextAutoGenerateTextPlugin *createTextAutogeneratePlugin() override;
    [[nodiscard]] TextAutogenerateText::TextAutoGenerateTextClient::EngineType engineType() const override;
    [[nodiscard]] bool hasConfigurationDialog() const override;
    [[nodiscard]] bool showConfigureDialog(QWidget *parentWidget) override;
    [[nodiscard]] QString webSite() const override;
    [[nodiscard]] QString modelName() const override;
};
