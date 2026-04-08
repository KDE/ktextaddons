/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserversseplugininterface.h"
#include "sse/mcpserversse.h"

McpServerSsePluginInterface::McpServerSsePluginInterface(QObject *parent)
    : McpProtocol::McpProtocolPluginInterface{parent}
    , mServerSse(new McpServerSse(this, this))
{
    connect(mServerSse, &McpServerSse::started, this, &McpServerSsePluginInterface::started);
    connect(mServerSse, &McpServerSse::received, this, &McpServerSsePluginInterface::received);
    connect(mServerSse, &McpServerSse::error, this, &McpServerSsePluginInterface::error);
    connect(mServerSse, &McpServerSse::finished, this, &McpServerSsePluginInterface::finished);
}

McpServerSsePluginInterface::~McpServerSsePluginInterface() = default;

void McpServerSsePluginInterface::start()
{
    mServerSse->connection();
}

void McpServerSsePluginInterface::send(const QJsonObject &obj)
{
    mServerSse->send(obj);
}

#include "moc_mcpserversseplugininterface.cpp"
