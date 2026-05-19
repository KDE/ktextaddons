/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientstdioplugininterface.h"
#include "stdio/mcpclientstdio.h"

McpClientStdioPluginInterface::McpClientStdioPluginInterface(QObject *parent)
    : TextAutoGenerateTextMcpProtocolCore::McpProtocolPluginInterface{parent}
    , mClientStdio(new McpClientStdio(this, this))
{
    connect(mClientStdio, &McpClientStdio::error, this, &McpClientStdioPluginInterface::error);
    connect(mClientStdio, &McpClientStdio::received, this, &McpClientStdioPluginInterface::received);
    connect(mClientStdio, &McpClientStdio::started, this, &McpClientStdioPluginInterface::started);
    connect(mClientStdio, &McpClientStdio::finished, this, &McpClientStdioPluginInterface::finished);
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
