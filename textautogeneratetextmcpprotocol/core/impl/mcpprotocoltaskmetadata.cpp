/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltaskmetadata.h"
#include <QDebug>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolTaskMetadata::McpProtocolTaskMetadata() = default;

bool McpProtocolTaskMetadata::operator==(const McpProtocolTaskMetadata &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolTaskMetadata &t)
{
    d.space() << "ttl:" << t.ttl();
    return d;
}

McpProtocolTaskMetadata McpProtocolTaskMetadata::fromJson(const QJsonObject &obj)
{
    McpProtocolTaskMetadata prompt;
    if (const QJsonValue ttlValue = obj.value("ttl"_L1); ttlValue.isDouble()) {
        prompt.setTtl(ttlValue.toInteger());
    }
    return prompt;
}

QJsonObject McpProtocolTaskMetadata::toJson(const McpProtocolTaskMetadata &taskMetadata)
{
    QJsonObject obj;
    if (taskMetadata.ttl().has_value()) {
        obj["ttl"_L1] = *taskMetadata.ttl();
    }
    return obj;
}

std::optional<qint64> McpProtocolTaskMetadata::ttl() const
{
    return mTtl;
}

void McpProtocolTaskMetadata::setTtl(std::optional<qint64> newTtl)
{
    mTtl = newTtl;
}
