/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mistralclient.h"
#include "mistralplugin.h"
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;
MistralClient::MistralClient(QObject *parent)
    : TextAutogenerateText::TextAutogenerateTextClient{parent}
{
}

MistralClient::~MistralClient() = default;

QString MistralClient::name() const
{
    return "mistral"_L1;
}

QString MistralClient::translatedName() const
{
    return i18n("Mistral AI");
}

TextAutogenerateText::TextAutogenerateTextPlugin *MistralClient::createTextAutogeneratePlugin()
{
    return new MistralPlugin(this);
}

TextAutogenerateText::TextAutogenerateTextClient::EngineType MistralClient::engineType() const
{
    return TextAutogenerateText::TextAutogenerateTextClient::Network;
}

bool MistralClient::hasConfigurationDialog() const
{
    return true;
}

bool MistralClient::showConfigureDialog(QWidget *parentWidget)
{
    // TODO
    return false;
}

#include "moc_mistralclient.cpp"
