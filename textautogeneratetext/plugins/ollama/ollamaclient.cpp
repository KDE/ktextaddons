/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaclient.h"
#include "ollamaconfiguredialog.h"
#include "ollamaplugin.h"
#include "ollamasettings.h"
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;
OllamaClient::OllamaClient(QObject *parent)
    : TextAutogenerateText::TextAutoGenerateTextClient{parent}
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

TextAutogenerateText::TextAutoGenerateTextPlugin *OllamaClient::createTextAutogeneratePlugin()
{
    return new OllamaPlugin(this);
}

TextAutogenerateText::TextAutoGenerateTextClient::EngineType OllamaClient::engineType() const
{
    return TextAutogenerateText::TextAutoGenerateTextClient::EngineType::Local;
}

bool OllamaClient::hasConfigurationDialog() const
{
    return true;
}

bool OllamaClient::showConfigureDialog(QWidget *parentWidget)
{
    // TODO use QPointer ?
    OllamaConfigureDialog d(parentWidget);
    return d.exec();
}

QString OllamaClient::webSite() const
{
    return QStringLiteral("https://ollama.com/");
}

QString OllamaClient::modelName() const
{
    return OllamaSettings::model();
}

#include "moc_ollamaclient.cpp"
