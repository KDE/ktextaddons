/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include <KPluginFactory>

#include "autogeneratetext_mcpprotocolserverplugin_debug.h"
#include "mcpserverplugin.h"
#include "sse/mcpserversseplugininterface.h"
#include "stdio/mcpserverstdioplugininterface.h"
#include "streamanblehttp/mcpserverstreamblehttpplugininterface.h"
K_PLUGIN_CLASS_WITH_JSON(McpServerPlugin, "mcpserverplugin.json")

McpServerPlugin::McpServerPlugin(QObject *parent, const QList<QVariant> &)
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

#include "mcpserverplugin.moc"
#include "moc_mcpserverplugin.cpp"
