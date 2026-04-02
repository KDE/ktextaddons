/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolplugininterface.h"

using namespace McpProtocol;
McpProtocolPluginInterface::McpProtocolPluginInterface(QObject *parent)
    : QObject{parent}
{
}

McpProtocolPluginInterface::~McpProtocolPluginInterface() = default;

#include "moc_mcpprotocolplugininterface.cpp"
