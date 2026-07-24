/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserverstreamhttp.h"

McpServerStreamHttp::McpServerStreamHttp(McpServerStreamHttpPluginInterface *interface, QObject *parent)
    : QObject{parent}
    , mInterface(interface)
{
}

McpServerStreamHttp::~McpServerStreamHttp() = default;

void McpServerStreamHttp::connection()
{
    // TODO
}

void McpServerStreamHttp::send(const QJsonObject &obj)
{
    // TODO
}
#include "moc_mcpserverstreamhttp.cpp"
