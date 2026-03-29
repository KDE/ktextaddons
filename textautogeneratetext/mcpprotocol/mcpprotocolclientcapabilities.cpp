/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolclientcapabilities.h"
#include <QDebug>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolClientCapabilities::McpProtocolClientCapabilities() = default;

McpProtocolClientCapabilities::~McpProtocolClientCapabilities() = default;

bool McpProtocolClientCapabilities::operator==(const McpProtocolClientCapabilities &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolClientCapabilities &t)
{
    return d;
}

McpProtocolClientCapabilities McpProtocolClientCapabilities::fromJson(const QJsonObject &obj)
{
    McpProtocolClientCapabilities modelHint;
    return modelHint;
}

QJsonObject McpProtocolClientCapabilities::toJson(const McpProtocolClientCapabilities &choice)
{
    QJsonObject obj;
    return obj;
}

#include "moc_mcpprotocolclientcapabilities.cpp"
