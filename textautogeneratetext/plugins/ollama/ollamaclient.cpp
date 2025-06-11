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
    , mManager(new OllamaManager(this))
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

TextAutoGenerateText::TextAutoGenerateTextPlugin *OllamaClient::createTextAutoGeneratePlugin()
{
    return new OllamaPlugin(mManager, this);
}

TextAutoGenerateText::TextAutoGenerateTextClient::EngineType OllamaClient::engineType() const
{
    return TextAutoGenerateText::TextAutoGenerateTextClient::EngineType::Local;
}

bool OllamaClient::hasConfigurationDialog() const
{
    return true;
}

bool OllamaClient::showConfigureDialog(QWidget *parentWidget)
{
    // TODO use QPointer ?
    OllamaConfigureDialog d(mManager, parentWidget);
    return d.exec();
}

QString OllamaClient::modelName() const
{
    return OllamaSettings::model();
}

QList<TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer> OllamaClient::supportedServers() const
{
    return {};
}
#include "moc_ollamaclient.cpp"
