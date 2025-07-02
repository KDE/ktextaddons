/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "genericnetworkclient.h"
#include "core/textautogeneratemanager.h"
#include "genericnetworkplugin.h"
#include "genericnetworkserverinfo.h"
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
    return "generic"_L1;
}

QString GenericNetworkClient::translatedName() const
{
    return i18n("Generic");
}

TextAutoGenerateText::TextAutoGenerateTextPlugin *
GenericNetworkClient::createTextAutoGeneratePlugin(TextAutoGenerateText::TextAutoGenerateManager *manager,
                                                   TextAutoGenerateText::TextAutoGenerateTextInstance *instance)
{
    auto plugin = new GenericNetworkPlugin(instance, manager, this);
    return plugin;
}

QList<TextAutoGenerateText::TextAutoGenerateTextClient::SupportedServer> GenericNetworkClient::supportedServers() const
{
    const GenericNetworkServerInfo info;
    return info.supportedServers(name());
}

#include "moc_genericnetworkclient.cpp"
