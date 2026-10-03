/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserverstreamhttpplugininterface.h"
#include "autogeneratetext_mcpprotocolserverplugin_lib_debug.h"
#include <KLocalizedString>

McpServerStreamHttpPluginInterface::McpServerStreamHttpPluginInterface(QObject *parent)
    : TextAutoGenerateTextMcpProtocolCore::McpProtocolPluginInterface{parent}
{
}

McpServerStreamHttpPluginInterface::~McpServerStreamHttpPluginInterface() = default;

void McpServerStreamHttpPluginInterface::start()
{
    // TODO implement it. Inform user otherwise client waits forever
    qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Streamable HTTP transport is not implemented yet.";
    Q_EMIT error(i18n("Streamable HTTP transport is not implemented yet."));
    Q_EMIT finished();
}

void McpServerStreamHttpPluginInterface::send(const QJsonObject &)
{
    // TODO
    qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Sending message is not implemented yet.";
    Q_EMIT error(i18n("Sending message is not implemented yet."));
}

#include "moc_mcpserverstreamhttpplugininterface.cpp"
