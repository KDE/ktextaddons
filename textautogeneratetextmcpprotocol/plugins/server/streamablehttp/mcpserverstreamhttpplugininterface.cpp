/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserverstreamhttpplugininterface.h"
#include "streamablehttp/mcpserverstreamablehttp.h"

McpServerStreamHttpPluginInterface::McpServerStreamHttpPluginInterface(QObject *parent)
    : TextAutoGenerateTextMcpProtocolCore::McpProtocolPluginInterface{parent}
    , mServerStreamableHttp(new McpServerStreamableHttp(this, this))
{
    connect(mServerStreamableHttp, &McpServerStreamableHttp::started, this, &McpServerStreamHttpPluginInterface::started);
    connect(mServerStreamableHttp, &McpServerStreamableHttp::received, this, &McpServerStreamHttpPluginInterface::received);
    connect(mServerStreamableHttp, &McpServerStreamableHttp::error, this, &McpServerStreamHttpPluginInterface::error);
    connect(mServerStreamableHttp, &McpServerStreamableHttp::finished, this, &McpServerStreamHttpPluginInterface::finished);
}

McpServerStreamHttpPluginInterface::~McpServerStreamHttpPluginInterface() = default;

void McpServerStreamHttpPluginInterface::start()
{
    mServerStreamableHttp->connection();
}

void McpServerStreamHttpPluginInterface::stop()
{
    mServerStreamableHttp->stop();
}

void McpServerStreamHttpPluginInterface::send(const QJsonObject &obj)
{
    mServerStreamableHttp->send(obj);
}

#include "moc_mcpserverstreamhttpplugininterface.cpp"
