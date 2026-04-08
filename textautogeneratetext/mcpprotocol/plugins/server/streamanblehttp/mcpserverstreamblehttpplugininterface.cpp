/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserverstreamblehttpplugininterface.h"

McpServerStreambleHttpPluginInterface::McpServerStreambleHttpPluginInterface(QObject *parent)
    : McpProtocol::McpProtocolPluginInterface{parent}
{
}

McpServerStreambleHttpPluginInterface::~McpServerStreambleHttpPluginInterface() = default;

void McpServerStreambleHttpPluginInterface::start()
{
    // TODO
}

void McpServerStreambleHttpPluginInterface::send(const QJsonObject &obj)
{
    // TODO
}

#include "moc_mcpserverstreamblehttpplugininterface.cpp"
