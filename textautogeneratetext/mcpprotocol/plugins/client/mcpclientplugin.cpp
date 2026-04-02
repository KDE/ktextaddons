/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientplugin.h"
#include "sse/mcpclientsseplugininterface.h"
// TODO #include "autogeneratetext_mcpprotocolclientplugin_debug.h"

McpClientPlugin::McpClientPlugin(QObject *parent)
    : McpProtocol::McpProtocolPlugin{parent}
{
    mPluginType = McpProtocol::McpProtocolPlugin::PluginType::Client;
}

McpClientPlugin::~McpClientPlugin() = default;

McpProtocol::McpProtocolPluginInterface *McpClientPlugin::createInterface(McpProtocol::McpProtocolPlugin::ProtocolType type, QObject *parent)
{
    switch (type) {
    case McpProtocol::McpProtocolPlugin::ProtocolType::Sse:
        return new McpClientSsePluginInterface(parent);
    case McpProtocol::McpProtocolPlugin::ProtocolType::Stdio:
        break;
    case McpProtocol::McpProtocolPlugin::ProtocolType::StreamableHttp:
        break;
    default:
        break;
    }
    // qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENTPLUGIN_LOG) << "There is a bug here !";
    Q_UNREACHABLE();
    return {};
}

#include "moc_mcpclientplugin.cpp"
