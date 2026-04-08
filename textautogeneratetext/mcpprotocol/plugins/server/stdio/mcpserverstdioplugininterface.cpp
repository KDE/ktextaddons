/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserverstdioplugininterface.h"
#include "stdio/mcpclientstdio.h"

McpServerStdioPluginInterface::McpServerStdioPluginInterface(QObject *parent)
    : McpProtocol::McpProtocolPluginInterface{parent}
    , mClientStdio(new McpClientStdio(this, this))
{
}

McpServerStdioPluginInterface::~McpServerStdioPluginInterface() = default;

void McpServerStdioPluginInterface::start()
{
    mClientStdio->connection();
}

void McpServerStdioPluginInterface::send(const QJsonObject &obj)
{
    mClientStdio->send(obj);
}

#include "moc_mcpserverstdioplugininterface.cpp"
