/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaclient.h"
#include "ollamaconfiguredialog.h"
#include "ollamamanager.h"
#include "ollamaplugin.h"
#include "ollamasettings.h"
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;
OllamaClient::OllamaClient(QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextClient{parent}

{
}

OllamaClient::~OllamaClient() = default;

QString OllamaClient::name() const
{
    return OllamaPlugin::name();
}

QString OllamaClient::translatedName() const
{
    return i18n("Ollama");
}

TextAutoGenerateText::TextAutoGenerateTextPlugin *OllamaClient::createTextAutoGeneratePlugin(TextAutoGenerateText::TextAutoGenerateManager *manager,
                                                                                             const QString &serverIdentifier)
{
    Q_UNUSED(serverIdentifier)
    return new OllamaPlugin(manager, this);
}

TextAutoGenerateText::TextAutoGenerateTextClient::EngineType OllamaClient::engineType() const
{
    return TextAutoGenerateText::TextAutoGenerateTextClient::EngineType::Local;
}

QString OllamaClient::modelName() const
{
    return OllamaSettings::model();
}

QList<TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer> OllamaClient::supportedServers() const
{
    const TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer info{
        .localizedName = translatedName(),
        .identifier = name(),
        .pluginName = name(),
    };
    return {info};
}
#include "moc_ollamaclient.cpp"
