/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientplugin.h"
#include "autogeneratetext_mcpprotocolclientplugin_debug.h"
#include "sse/mcpclientsseplugininterface.h"
#include "stdio/mcpclientstdioplugininterface.h"

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
        return new McpClientStdioPluginInterface(parent);
    case McpProtocol::McpProtocolPlugin::ProtocolType::StreamableHttp:
        qCDebug(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LOG) << "Not implemented yet." << type;
        break;
    default:
        break;
    }
    qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LOG) << "There is a bug here !";
    Q_UNREACHABLE();
    return {};
}

#include "moc_mcpclientplugin.cpp"
