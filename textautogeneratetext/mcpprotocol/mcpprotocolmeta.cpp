/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolmeta.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolMeta::McpProtocolMeta() = default;

McpProtocolMeta::~McpProtocolMeta() = default;

bool McpProtocolMeta::operator==(const McpProtocolMeta &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolMeta &t)
{
    d.space() << "meta:" << t.meta();
    return d;
}

McpProtocolMeta McpProtocolMeta::fromJson(const QJsonObject &obj)
{
    McpProtocolMeta prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        const QJsonObject mapObj = obj["_meta"_L1].toObject();
        QMap<QString, QJsonValue> map;
        for (auto it = mapObj.constBegin(); it != mapObj.constEnd(); ++it) {
            map.insert(it.key(), it.value());
        }
        prompt.setMeta(map);
    }
    return prompt;
}

QJsonObject McpProtocolMeta::toJson(const McpProtocolMeta &protocolMeta)
{
    QJsonObject obj;
    if (protocolMeta.meta().has_value()) {
        const auto meta = protocolMeta.meta();
        QJsonObject map;
        for (auto it = meta->constBegin(); it != meta->constEnd(); ++it) {
            map.insert(it.key(), it.value());
        }
        obj["_meta"_L1] = map;
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
