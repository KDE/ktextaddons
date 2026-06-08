/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolservercapabilities.h"
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolServerCapabilities::McpProtocolServerCapabilities() = default;

McpProtocolServerCapabilities::~McpProtocolServerCapabilities() = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities &t)
{
    // TODO
    return d;
}

bool McpProtocolServerCapabilities::operator==(const McpProtocolServerCapabilities &other) const = default;

McpProtocolServerCapabilities McpProtocolServerCapabilities::fromJson(const QJsonObject &obj)
{
    return {};
}

QJsonObject McpProtocolServerCapabilities::toJson(const McpProtocolServerCapabilities &image)
{
    return {};
}
