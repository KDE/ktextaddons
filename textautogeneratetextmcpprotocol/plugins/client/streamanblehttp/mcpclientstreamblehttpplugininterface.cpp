/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientstreamblehttpplugininterface.h"
#include "streamanblehttp/mcpclientstreamablehttp.h"

McpClientStreambleHttpPluginInterface::McpClientStreambleHttpPluginInterface(QObject *parent)
    : TextAutoGenerateTextMcpProtocolCore::McpProtocolPluginInterface{parent}
    , mClientStreamableHttp(new McpClientStreamableHttp(this, this))
{
    connect(mClientStreamableHttp, &McpClientStreamableHttp::started, this, &McpClientStreambleHttpPluginInterface::started);
    connect(mClientStreamableHttp, &McpClientStreamableHttp::received, this, &McpClientStreambleHttpPluginInterface::received);
    connect(mClientStreamableHttp, &McpClientStreamableHttp::error, this, &McpClientStreambleHttpPluginInterface::error);
    connect(mClientStreamableHttp, &McpClientStreamableHttp::finished, this, &McpClientStreambleHttpPluginInterface::finished);
}

McpClientStreambleHttpPluginInterface::~McpClientStreambleHttpPluginInterface() = default;

void McpClientStreambleHttpPluginInterface::start()
{
    mClientStreamableHttp->connection();
}

void McpClientStreambleHttpPluginInterface::send(const QJsonObject &obj)
{
    mClientStreamableHttp->send(obj);
}

#include "moc_mcpclientstreamblehttpplugininterface.cpp"
