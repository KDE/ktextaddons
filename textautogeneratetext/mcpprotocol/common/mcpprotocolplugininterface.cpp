/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolplugininterface.h"
#include "common/mcpprotocolsettings.h"

using namespace McpProtocol;
McpProtocolPluginInterface::McpProtocolPluginInterface(QObject *parent)
    : QObject{parent}
{
}

McpProtocolPluginInterface::~McpProtocolPluginInterface() = default;

void McpProtocolPluginInterface::setSettings(McpProtocolSettings *settings)
{
    mProtocolSettings.reset(settings);
}

#include "moc_mcpprotocolplugininterface.cpp"
