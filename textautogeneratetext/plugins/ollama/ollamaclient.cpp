/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaclient.h"
#include "ollamaplugin.h"
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;
OllamaClient::OllamaClient(QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextClient{parent}

{
}

OllamaClient::~OllamaClient() = default;

QString OllamaClient::name() const
{
    return "ollama"_L1;
}

QString OllamaClient::translatedName() const
{
    return i18n("Ollama");
}

TextAutoGenerateText::TextAutoGenerateTextPlugin *OllamaClient::createTextAutoGeneratePlugin(TextAutoGenerateText::TextAutoGenerateManager *manager,
                                                                                             TextAutoGenerateText::TextAutoGenerateTextInstance *instance)
{
    return new OllamaPlugin(manager, instance, this);
}

QList<TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer> OllamaClient::supportedServers() const
{
    const TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer info{
        .localizedName = QStringLiteral("%1 (%2)").arg(
            translatedName(),
            TextAutoGenerateText::TextAutoGenerateTextPlugin::convertEngineType(TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType::Local)),
        .identifier = name(),
        .pluginName = name(),
    };
    return {info};
}
#include "moc_ollamaclient.cpp"
