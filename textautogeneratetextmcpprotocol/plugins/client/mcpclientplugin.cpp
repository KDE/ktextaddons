/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include <KPluginFactory>

#include "autogeneratetext_mcpprotocolclientplugin_debug.h"
#include "mcpclientplugin.h"
#include "sse/mcpclientsseplugininterface.h"
#include "stdio/mcpclientstdioplugininterface.h"
#include "streamablehttp/mcpclientstreamablehttpplugininterface.h"
K_PLUGIN_CLASS_WITH_JSON(McpClientPlugin, "mcpclientplugin.json")

McpClientPlugin::McpClientPlugin(QObject *parent, const QList<QVariant> &)
    : TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin{parent}
{
    mPluginType = TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::PluginType::Client;
}

McpClientPlugin::~McpClientPlugin() = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolPluginInterface *
McpClientPlugin::createInterface(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType type, QObject *parent)
{
    switch (type) {
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Sse:
        return new McpClientSsePluginInterface(parent);
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Stdio:
        return new McpClientStdioPluginInterface(parent);
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::StreamableHttp:
        return new McpClientStreamableHttpPluginInterface(parent);
    default:
        break;
    }
    qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LOG) << "Invalid transport type:" << type;
    return nullptr;
}

#include "mcpclientplugin.moc"
#include "moc_mcpclientplugin.cpp"
