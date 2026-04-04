/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientsseplugininterface.h"
#include "sse/mcpclientsse.h"

McpClientSsePluginInterface::McpClientSsePluginInterface(QObject *parent)
    : McpProtocol::McpProtocolPluginInterface{parent}
    , mClientSse(new McpClientSse(this))
{
    connect(mClientSse, &McpClientSse::started, this, &McpClientSsePluginInterface::started);
    connect(mClientSse, &McpClientSse::received, this, &McpClientSsePluginInterface::received);
    connect(mClientSse, &McpClientSse::error, this, &McpClientSsePluginInterface::error);
    connect(mClientSse, &McpClientSse::finished, this, &McpClientSsePluginInterface::finished);
}

McpClientSsePluginInterface::~McpClientSsePluginInterface() = default;

void McpClientSsePluginInterface::start()
{
    mClientSse->connection();
    // TODO
}

#include "moc_mcpclientsseplugininterface.cpp"
