/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientstdioplugininterface.h"

McpClientStdioPluginInterface::McpClientStdioPluginInterface(QObject *parent)
    : McpProtocol::McpProtocolPluginInterface{parent}
{
}

McpClientStdioPluginInterface::~McpClientStdioPluginInterface() = default;

#include "moc_mcpclientstdioplugininterface.cpp"
