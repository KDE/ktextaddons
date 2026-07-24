/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserverstreamhttpplugininterface.h"

McpServerStreamHttpPluginInterface::McpServerStreamHttpPluginInterface(QObject *parent)
    : TextAutoGenerateTextMcpProtocolCore::McpProtocolPluginInterface{parent}
{
}

McpServerStreamHttpPluginInterface::~McpServerStreamHttpPluginInterface() = default;

void McpServerStreamHttpPluginInterface::start()
{
    // TODO
}

void McpServerStreamHttpPluginInterface::send(const QJsonObject &obj)
{
    // TODO
}

#include "moc_mcpserverstreamhttpplugininterface.cpp"
