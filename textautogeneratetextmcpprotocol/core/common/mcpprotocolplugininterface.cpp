/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolplugininterface.h"
#include "common/mcpprotocolsettings.h"

using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolPluginInterface::McpProtocolPluginInterface(QObject *parent)
    : QObject{parent}
{
}

McpProtocolPluginInterface::~McpProtocolPluginInterface() = default;

void McpProtocolPluginInterface::setSettings(McpProtocolSettings *settings)
{
    mProtocolSettings.reset(settings);
}

bool McpProtocolPluginInterface::canStart() const
{
    return mProtocolSettings.get() != nullptr;
}

QVariant McpProtocolPluginInterface::connectionInfo() const
{
    return mProtocolSettings->connectionInfo();
}

#include "moc_mcpprotocolplugininterface.cpp"
