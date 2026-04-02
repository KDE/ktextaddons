/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserverplugin.h"
#include "autogeneratetext_mcpprotocolserverplugin_debug.h"

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
    case McpProtocol::McpProtocolPlugin::ProtocolType::Stdio:
    case McpProtocol::McpProtocolPlugin::ProtocolType::StreamableHttp:
        qCDebug(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LOG) << "Not implemented yet." << type;
        break;
    default:
        break;
    }
    qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LOG) << "There is a bug here !";
    Q_UNREACHABLE();
    return {};
}

#include "moc_mcpserverplugin.cpp"
