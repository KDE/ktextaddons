/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolnotificationparams.h"
#include <QDebug>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolNotificationParams::McpProtocolNotificationParams() = default;

McpProtocolNotificationParams::~McpProtocolNotificationParams() = default;

bool McpProtocolNotificationParams::operator==(const McpProtocolNotificationParams &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolNotificationParams &t)
{
    d.space() << "meta:" << t.meta();
    return d;
}

McpProtocolNotificationParams McpProtocolNotificationParams::fromJson(const QJsonObject &obj)
{
    McpProtocolNotificationParams prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    return prompt;
}

QJsonObject McpProtocolNotificationParams::toJson(const McpProtocolNotificationParams &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolNotificationParams::meta() const
{
    return mMeta;
}

void McpProtocolNotificationParams::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}
