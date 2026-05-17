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
    : TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin{parent}
{
    mPluginType = TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::PluginType::Server;
}

McpServerPlugin::~McpServerPlugin() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolPluginInterface *
McpServerPlugin::createInterface(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType type, QObject *parent)
{
    switch (type) {
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Sse:
        return new McpServerSsePluginInterface(parent);
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Stdio:
        return new McpServerStdioPluginInterface(parent);
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::StreamableHttp:
        return new McpServerStreambleHttpPluginInterface(parent);
    default:
        break;
    }
    qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LOG) << "There is a bug here !";
    Q_UNREACHABLE();
    return {};
}

#include "mcpserverplugin.moc"
#include "moc_mcpserverplugin.cpp"
