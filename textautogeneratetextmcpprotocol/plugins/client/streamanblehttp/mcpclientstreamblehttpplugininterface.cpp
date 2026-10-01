/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientstreamblehttpplugininterface.h"
#include "autogeneratetext_mcpprotocolclientplugin_lib_debug.h"
#include <KLocalizedString>

McpClientStreambleHttpPluginInterface::McpClientStreambleHttpPluginInterface(QObject *parent)
    : TextAutoGenerateTextMcpProtocolCore::McpProtocolPluginInterface{parent}
{
}

McpClientStreambleHttpPluginInterface::~McpClientStreambleHttpPluginInterface() = default;

void McpClientStreambleHttpPluginInterface::start()
{
    // TODO
}

void McpClientStreambleHttpPluginInterface::send(const QJsonObject &)
{
    // TODO
    qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Sending message is not implemented yet.";
    Q_EMIT error(i18n("Sending message is not implemented yet."));
}

#include "moc_mcpclientstreamblehttpplugininterface.cpp"
