/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <TextAutoGenerateText/TextAutoGenerateTextClient>
class GenericNetworkClient : public TextAutoGenerateText::TextAutoGenerateTextClient
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.TextAutoGenerateText.genericnetwork")
    Q_INTERFACES(TextAutoGenerateText::TextAutoGenerateTextClient)
public:
    explicit GenericNetworkClient(QObject *parent = nullptr);
    ~GenericNetworkClient() override;

    [[nodiscard]] QString name() const override;
    [[nodiscard]] QString translatedName() const override;
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateTextPlugin *
    createTextAutoGeneratePlugin(TextAutoGenerateText::TextAutoGenerateManager *manager, TextAutoGenerateText::TextAutoGenerateTextInstance *instance) override;
    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer> supportedServers() const override;
};
