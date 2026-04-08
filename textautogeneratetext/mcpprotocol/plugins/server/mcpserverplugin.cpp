/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserverplugin.h"
#include "autogeneratetext_mcpprotocolserverplugin_debug.h"
#include "sse/mcpserversseplugininterface.h"
#include "stdio/mcpserverstdioplugininterface.h"
#include "streamanblehttp/mcpserverstreamblehttpplugininterface.h"

McpServerPlugin::McpServerPlugin(QObject *parent)
    : McpProtocol::McpProtocolPlugin{parent}
{
    mPluginType = McpProtocol::McpProtocolPlugin::PluginType::Server;
}

McpServerPlugin::~McpServerPlugin() = default;

McpProtocol::McpProtocolPluginInterface *McpServerPlugin::createInterface(McpProtocol::McpProtocolPlugin::ProtocolType type, QObject *parent)
{
    switch (type) {
    case McpProtocol::McpProtocolPlugin::ProtocolType::Sse:
        return new McpServerSsePluginInterface(this);
    case McpProtocol::McpProtocolPlugin::ProtocolType::Stdio:
        return new McpServerStdioPluginInterface(this);
    case McpProtocol::McpProtocolPlugin::ProtocolType::StreamableHttp:
        return new McpServerStreambleHttpPluginInterface(this);
    default:
        break;
    }
    qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LOG) << "There is a bug here !";
    Q_UNREACHABLE();
    return {};
}

#include "moc_mcpserverplugin.cpp"
