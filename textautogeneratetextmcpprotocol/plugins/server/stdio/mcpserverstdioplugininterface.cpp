/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserverstdioplugininterface.h"
#include "stdio/mcpserverstdio.h"

McpServerStdioPluginInterface::McpServerStdioPluginInterface(QObject *parent)
    : TextAutoGenerateTextMcpProtocolCore::McpProtocolPluginInterface{parent}
    , mServerStdio(new McpServerStdio(this, this))
{
}

McpServerStdioPluginInterface::~McpServerStdioPluginInterface() = default;

void McpServerStdioPluginInterface::start()
{
    mServerStdio->connection();
}

void McpServerStdioPluginInterface::send(const QJsonObject &obj)
{
    mServerStdio->send(obj);
}

#include "moc_mcpserverstdioplugininterface.cpp"
