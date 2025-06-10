/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "genericnetworkclient.h"
#include <KLocalizedString>
#include <qt6keychain/keychain.h>

using namespace Qt::Literals::StringLiterals;
GenericNetworkClient::GenericNetworkClient(QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextClient{parent}
{
}

GenericNetworkClient::~GenericNetworkClient() = default;

QString GenericNetworkClient::name() const
{
    return "mistral"_L1;
}

QString GenericNetworkClient::translatedName() const
{
    return i18n("Mistral AI");
}

TextAutoGenerateText::TextAutoGenerateTextPlugin *GenericNetworkClient::createTextAutoGeneratePlugin()
{
    return {};
    // new MistralPlugin(mManager, this);
}

TextAutoGenerateText::TextAutoGenerateTextClient::EngineType GenericNetworkClient::engineType() const
{
    return TextAutoGenerateText::TextAutoGenerateTextClient::EngineType::Network;
}

bool GenericNetworkClient::hasConfigurationDialog() const
{
    return true;
}

bool GenericNetworkClient::showConfigureDialog(QWidget *parentWidget)
{
    return true;
}

QString GenericNetworkClient::webSite() const
{
    return QStringLiteral("https://chat.mistral.ai/");
}

QString GenericNetworkClient::modelName() const
{
    // No model here
    return {};
}

#include "moc_genericnetworkclient.cpp"
