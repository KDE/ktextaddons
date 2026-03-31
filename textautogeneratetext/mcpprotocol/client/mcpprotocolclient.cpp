/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolclient.h"

using namespace McpProtocol;
using namespace Qt::Literals::StringLiterals;
McpProtocolClient::McpProtocolClient(QObject *parent)
    : QObject{parent}
{
}

McpProtocolClient::~McpProtocolClient() = default;
