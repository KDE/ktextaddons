/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltaskmetadata.h"
#include <QDebug>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolTaskMetadata::McpProtocolTaskMetadata() = default;

McpProtocolTaskMetadata::~McpProtocolTaskMetadata() = default;

bool McpProtocolTaskMetadata::operator==(const McpProtocolTaskMetadata &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolTaskMetadata &t)
{
    d.space() << "ttl:" << t.ttl();
    return d;
}

McpProtocolTaskMetadata McpProtocolTaskMetadata::fromJson(const QJsonObject &obj)
{
    McpProtocolTaskMetadata prompt;
    if (obj.contains("ttl"_L1)) {
        prompt.setTtl(obj.value("ttl"_L1).toInt());
    }
    return prompt;
}

QJsonObject McpProtocolTaskMetadata::toJson(const McpProtocolTaskMetadata &boolean)
{
    QJsonObject obj;
    if (boolean.ttl().has_value()) {
        obj["ttl"_L1] = *boolean.ttl();
    }
    return obj;
}

std::optional<int> McpProtocolTaskMetadata::ttl() const
{
    return mTtl;
}

void McpProtocolTaskMetadata::setTtl(std::optional<int> newTtl)
{
    mTtl = newTtl;
}
