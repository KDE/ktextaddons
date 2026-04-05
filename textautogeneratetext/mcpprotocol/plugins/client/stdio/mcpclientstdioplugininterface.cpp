/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientstdioplugininterface.h"
#include "stdio/mcpclientstdio.h"

McpClientStdioPluginInterface::McpClientStdioPluginInterface(QObject *parent)
    : McpProtocol::McpProtocolPluginInterface{parent}
    , mClientStdio(new McpClientStdio(this, this))
{
}

McpClientStdioPluginInterface::~McpClientStdioPluginInterface() = default;

void McpClientStdioPluginInterface::start()
{
    mClientStdio->connection();
}

void McpClientStdioPluginInterface::send(const QJsonObject &obj)
{
    mClientStdio->send(obj);
}

#include "moc_mcpclientstdioplugininterface.cpp"
