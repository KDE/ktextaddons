/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolmeta.h"
#include <QDebug>
#include <QJsonObject>

using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolMeta::McpProtocolMeta() = default;

bool McpProtocolMeta::operator==(const McpProtocolMeta &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolMeta &t)
{
    d.space() << "meta:" << t.meta();
    return d;
}

McpProtocolMeta McpProtocolMeta::fromJson(const QJsonObject &obj)
{
    McpProtocolMeta protocolMeta;
    QMap<QString, QJsonValue> map;
    for (auto it = obj.constBegin(); it != obj.constEnd(); ++it) {
        map.insert(it.key(), it.value());
    }
    protocolMeta.setMeta(std::move(map));
    return protocolMeta;
}

QJsonObject McpProtocolMeta::toJson(const McpProtocolMeta &protocolMeta)
{
    QJsonObject obj;
    if (const auto meta = protocolMeta.meta(); meta.has_value()) {
        for (auto it = meta->constBegin(); it != meta->constEnd(); ++it) {
            obj.insert(it.key(), it.value());
        }
    }
    return obj;
}

std::optional<QMap<QString, QJsonValue>> McpProtocolMeta::meta() const
{
    return mMeta;
}

void McpProtocolMeta::setMeta(std::optional<QMap<QString, QJsonValue>> newMeta)
{
    mMeta = std::move(newMeta);
}
