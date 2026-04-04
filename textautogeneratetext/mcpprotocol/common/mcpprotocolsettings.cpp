/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolsettings.h"

using namespace McpProtocol;
McpProtocolSettings::McpProtocolSettings() = default;

McpProtocolSettings::~McpProtocolSettings() = default;

QVariant McpProtocolSettings::serverInfo() const
{
    return mServerInfo;
}

void McpProtocolSettings::setServerInfo(const QVariant &newServerInfo)
{
    mServerInfo = newServerInfo;
}
