/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientplugin.h"

McpClientPlugin::McpClientPlugin(QObject *parent)
    : McpProtocol::McpProtocolPlugin{parent}
{
}

McpClientPlugin::~McpClientPlugin() = default;

McpProtocol::McpProtocolPluginInterface *McpClientPlugin::createInterface(InterfaceType type, QObject *parent)
{
    // TODO
    return {};
}
