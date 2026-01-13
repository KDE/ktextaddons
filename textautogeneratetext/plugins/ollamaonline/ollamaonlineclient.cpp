/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaonlineclient.h"
#include "ollamaonlineplugin.h"
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;
OllamaOnlineClient::OllamaOnlineClient(QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextClient{parent}
{
}

OllamaOnlineClient::~OllamaOnlineClient() = default;

QString OllamaOnlineClient::name() const
{
    return "ollamaonline"_L1;
}

QString OllamaOnlineClient::translatedName() const
{
    return i18n("Ollama (Online)");
}

TextAutoGenerateText::TextAutoGenerateTextPlugin *OllamaOnlineClient::createTextAutoGeneratePlugin(TextAutoGenerateText::TextAutoGenerateManager *manager,
                                                                                                   TextAutoGenerateText::TextAutoGenerateTextInstance *instance)
{
    return new OllamaOnlinePlugin(manager, instance, this);
}

QList<TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer> OllamaOnlineClient::supportedServers() const
{
    const TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer info{
        .localizedName = QStringLiteral("%1 (%2)").arg(
            translatedName(),
            TextAutoGenerateText::TextAutoGenerateTextPlugin::convertEngineType(TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType::Network)),
        .identifier = name(),
        .pluginName = name(),
    };
    return {info};
}
#include "moc_ollamaonlineclient.cpp"
