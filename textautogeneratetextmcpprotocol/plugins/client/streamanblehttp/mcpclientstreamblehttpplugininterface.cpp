/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientstreamblehttpplugininterface.h"

McpClientStreambleHttpPluginInterface::McpClientStreambleHttpPluginInterface(QObject *parent)
    : TextAutoGenerateTextMcpProtocolCore::McpProtocolPluginInterface{parent}
{
}

McpClientStreambleHttpPluginInterface::~McpClientStreambleHttpPluginInterface() = default;

void McpClientStreambleHttpPluginInterface::start()
{
    // TODO
}

void McpClientStreambleHttpPluginInterface::send(const QJsonObject &obj)
{
    // TODO
}

#include "moc_mcpclientstreamblehttpplugininterface.cpp"
