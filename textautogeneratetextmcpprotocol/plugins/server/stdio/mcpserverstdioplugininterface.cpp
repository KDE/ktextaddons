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
    connect(mServerStdio, &McpServerStdio::started, this, &McpServerStdioPluginInterface::started);
    connect(mServerStdio, &McpServerStdio::received, this, &McpServerStdioPluginInterface::received);
    connect(mServerStdio, &McpServerStdio::error, this, &McpServerStdioPluginInterface::error);
    connect(mServerStdio, &McpServerStdio::finished, this, &McpServerStdioPluginInterface::finished);
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
