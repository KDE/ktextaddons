/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolsettings.h"

using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSettings::McpProtocolSettings() = default;

McpProtocolSettings::~McpProtocolSettings() = default;

QVariant McpProtocolSettings::connectionInfo() const
{
    return mConnectionInfo;
}

void McpProtocolSettings::setConnectionInfo(const QVariant &newConnectionInfo)
{
    mConnectionInfo = newConnectionInfo;
}
