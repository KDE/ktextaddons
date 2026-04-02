/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientsseplugininterface.h"

McpClientSsePluginInterface::McpClientSsePluginInterface(QObject *parent)
    : McpProtocol::McpProtocolPluginInterface{parent}
{
}

McpClientSsePluginInterface::~McpClientSsePluginInterface() = default;
