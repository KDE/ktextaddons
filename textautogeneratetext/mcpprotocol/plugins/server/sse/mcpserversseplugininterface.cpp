/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserversseplugininterface.h"
#include "sse/mcpclientsse.h"

McpServerSsePluginInterface::McpServerSsePluginInterface(QObject *parent)
    : McpProtocol::McpProtocolPluginInterface{parent}
    , mClientSse(new McpClientSse(this, this))
{
    connect(mClientSse, &McpClientSse::started, this, &McpServerSsePluginInterface::started);
    connect(mClientSse, &McpClientSse::received, this, &McpServerSsePluginInterface::received);
    connect(mClientSse, &McpClientSse::error, this, &McpServerSsePluginInterface::error);
    connect(mClientSse, &McpClientSse::finished, this, &McpServerSsePluginInterface::finished);
}

McpServerSsePluginInterface::~McpServerSsePluginInterface() = default;

void McpServerSsePluginInterface::start()
{
    mClientSse->connection();
}

void McpServerSsePluginInterface::send(const QJsonObject &obj)
{
    mClientSse->send(obj);
}

#include "moc_mcpserversseplugininterface.cpp"
