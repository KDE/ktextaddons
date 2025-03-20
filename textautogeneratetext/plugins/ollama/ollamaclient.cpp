/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaclient.h"
#include "ollamaconfiguredialog.h"
#include "ollamaplugin.h"
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;
OllamaClient::OllamaClient(QObject *parent)
    : TextAutogenerateText::TextAutogenerateTextClient{parent}
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

TextAutogenerateText::TextAutogenerateTextPlugin *OllamaClient::createTextAutogeneratePlugin()
{
    return new OllamaPlugin(this);
}

TextAutogenerateText::TextAutogenerateTextClient::EngineType OllamaClient::engineType() const
{
    return TextAutogenerateText::TextAutogenerateTextClient::EngineType::Local;
}

bool OllamaClient::hasConfigurationDialog() const
{
    return true;
}

bool OllamaClient::showConfigureDialog(QWidget *parentWidget)
{
    // TODO use QPointer ?
    OllamaConfigureDialog d;
    return d.exec();
}

#include "moc_ollamaclient.cpp"
