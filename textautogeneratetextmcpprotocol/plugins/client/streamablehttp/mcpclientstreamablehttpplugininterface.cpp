/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientstreamablehttpplugininterface.h"
#include "streamablehttp/mcpclientstreamablehttp.h"

McpClientStreamableHttpPluginInterface::McpClientStreamableHttpPluginInterface(QObject *parent)
    : TextAutoGenerateTextMcpProtocolCore::McpProtocolPluginInterface{parent}
    , mClientStreamableHttp(new McpClientStreamableHttp(this, this))
{
    connect(mClientStreamableHttp, &McpClientStreamableHttp::started, this, &McpClientStreamableHttpPluginInterface::started);
    connect(mClientStreamableHttp, &McpClientStreamableHttp::received, this, &McpClientStreamableHttpPluginInterface::received);
    connect(mClientStreamableHttp, &McpClientStreamableHttp::error, this, &McpClientStreamableHttpPluginInterface::error);
    connect(mClientStreamableHttp, &McpClientStreamableHttp::finished, this, &McpClientStreamableHttpPluginInterface::finished);
}

McpClientStreamableHttpPluginInterface::~McpClientStreamableHttpPluginInterface() = default;

void McpClientStreamableHttpPluginInterface::start()
{
    mClientStreamableHttp->connection();
}

void McpClientStreamableHttpPluginInterface::stop()
{
    mClientStreamableHttp->stop();
}

void McpClientStreamableHttpPluginInterface::send(const QJsonObject &obj)
{
    mClientStreamableHttp->send(obj);
}

#include "moc_mcpclientstreamablehttpplugininterface.cpp"
