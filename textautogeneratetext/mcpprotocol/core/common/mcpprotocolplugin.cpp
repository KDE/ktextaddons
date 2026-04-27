/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolplugin.h"

using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolPlugin::McpProtocolPlugin(QObject *parent)
    : QObject{parent}
{
}

McpProtocolPlugin::~McpProtocolPlugin() = default;

McpProtocolPlugin::PluginType McpProtocolPlugin::pluginType() const
{
    return mPluginType;
}

#include "moc_mcpprotocolplugin.cpp"
