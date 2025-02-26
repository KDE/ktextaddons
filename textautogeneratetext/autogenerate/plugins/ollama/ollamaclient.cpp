/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaclient.h"
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
    // TODO
    return nullptr;
}

TextAutogenerateText::TextAutogenerateTextClient::EngineType OllamaClient::engineType() const
{
    return TextAutogenerateText::TextAutogenerateTextClient::Local;
}

bool OllamaClient::hasConfigurationDialog() const
{
    return true;
}

bool OllamaClient::showConfigureDialog(QWidget *parentWidget)
{
    // TODO
    return false;
}
