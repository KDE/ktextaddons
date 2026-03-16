/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolannotations.h"
#include <QDebug>
using namespace McpProtocol;
McpProtocolAnnotations::McpProtocolAnnotations() = default;

McpProtocolAnnotations::~McpProtocolAnnotations() = default;

bool McpProtocolAnnotations::operator==(const McpProtocolAnnotations &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolAnnotations &t)
{
    return d;
}
