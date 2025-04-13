/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mistralclient.h"
#include "mistralconfiguredialog.h"
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
    return TextAutogenerateText::TextAutogenerateTextClient::EngineType::Network;
}

bool MistralClient::hasConfigurationDialog() const
{
    return true;
}

bool MistralClient::showConfigureDialog(QWidget *parentWidget)
{
    // TODO use QPointer here ???
    MistralConfigureDialog d(parentWidget);
    return d.exec();
}

QString MistralClient::webSite() const
{
    return QStringLiteral("https://chat.mistral.ai/");
}

QString MistralClient::modelName() const
{
    // No model here
    return {};
}

#include "moc_mistralclient.cpp"
