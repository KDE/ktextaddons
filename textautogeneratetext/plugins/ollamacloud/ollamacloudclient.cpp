/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamacloudclient.h"
#include "ollamacloudplugin.h"
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;
OllamaCloudClient::OllamaCloudClient(QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextClient{parent}
{
}

OllamaCloudClient::~OllamaCloudClient() = default;

QString OllamaCloudClient::name() const
{
    return "ollamacloud"_L1;
}

QString OllamaCloudClient::translatedName() const
{
    return i18n("Ollama (Cloud)");
}

TextAutoGenerateText::TextAutoGenerateTextPlugin *OllamaCloudClient::createTextAutoGeneratePlugin(TextAutoGenerateText::TextAutoGenerateManager *manager,
                                                                                                  TextAutoGenerateText::TextAutoGenerateTextInstance *instance)
{
    return new OllamaCloudPlugin(manager, instance, this);
}

QList<TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer> OllamaCloudClient::supportedServers() const
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
#include "moc_ollamacloudclient.cpp"
