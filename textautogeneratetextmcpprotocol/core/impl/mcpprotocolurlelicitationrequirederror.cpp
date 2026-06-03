/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolurlelicitationrequirederror.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolURLElicitationRequiredError::McpProtocolURLElicitationRequiredError() = default;

McpProtocolURLElicitationRequiredError::~McpProtocolURLElicitationRequiredError() = default;

bool McpProtocolURLElicitationRequiredError::operator==(const McpProtocolURLElicitationRequiredError &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolURLElicitationRequiredError &t)
{
    return d;
}

McpProtocolURLElicitationRequiredError McpProtocolURLElicitationRequiredError::fromJson(const QJsonObject &obj)
{
    McpProtocolURLElicitationRequiredError prompt;
    return prompt;
}

QJsonObject McpProtocolURLElicitationRequiredError::toJson(const McpProtocolURLElicitationRequiredError &boolean)
{
    QJsonObject obj;
    return obj;
}
