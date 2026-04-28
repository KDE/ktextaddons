/*
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <TextAutoGenerateText/TextAutoGenerateTextClient>
class LMStudioClient : public TextAutoGenerateText::TextAutoGenerateTextClient
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.TextAutoGenerateText.lmstudio")
    Q_INTERFACES(TextAutoGenerateText::TextAutoGenerateTextClient)
public:
    explicit LMStudioClient(QObject *parent = nullptr);
    ~LMStudioClient() override;

    [[nodiscard]] QString name() const override;
    [[nodiscard]] QString translatedName() const override;
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateTextPlugin *
    createTextAutoGeneratePlugin(TextAutoGenerateText::TextAutoGenerateManager *manager, TextAutoGenerateText::TextAutoGenerateTextInstance *instance) override;
    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer> supportedServers() const override;
};
