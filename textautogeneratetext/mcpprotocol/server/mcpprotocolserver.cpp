/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolserver.h"

using namespace McpProtocol;
using namespace Qt::Literals::StringLiterals;

McpProtocolServer::McpProtocolServer(QObject *parent)
    : QObject{parent}
{
}

McpProtocolServer::~McpProtocolServer() = default;

#include "moc_mcpprotocolserver.cpp"
