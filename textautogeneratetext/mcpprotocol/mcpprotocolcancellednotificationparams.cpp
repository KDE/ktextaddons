/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcancellednotificationparams.h"
#include <QDebug>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolCancelledNotificationParams::McpProtocolCancelledNotificationParams() = default;

McpProtocolCancelledNotificationParams::~McpProtocolCancelledNotificationParams() = default;

bool McpProtocolCancelledNotificationParams::operator==(const McpProtocolCancelledNotificationParams &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolCancelledNotificationParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "reason:" << t.reason();
    d.space() << "requestId:" << t.requestId();
    return d;
}

McpProtocolCancelledNotificationParams McpProtocolCancelledNotificationParams::fromJson(const QJsonObject &obj)
{
    McpProtocolCancelledNotificationParams prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    if (obj.contains("reason"_L1)) {
        prompt.setReason(obj.value("reason"_L1).toString());
    }
    if (obj.contains("requestId"_L1)) {
        prompt.setRequestId(McpProtocolUtils::requestIdFromJson(obj["requestId"_L1]));
    }
    return prompt;
}

QJsonObject McpProtocolCancelledNotificationParams::toJson(const McpProtocolCancelledNotificationParams &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    if (boolean.reason().has_value()) {
        obj["reason"_L1] = *boolean.reason();
    }
    if (boolean.requestId().has_value()) {
        obj["requestId"_L1] = McpProtocolUtils::requestIdToJson(*boolean.requestId());
    }
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolCancelledNotificationParams::meta() const
{
    return mMeta;
}

void McpProtocolCancelledNotificationParams::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<QString> McpProtocolCancelledNotificationParams::reason() const
{
    return mReason;
}

void McpProtocolCancelledNotificationParams::setReason(std::optional<QString> newReason)
{
    mReason = std::move(newReason);
}

std::optional<McpProtocolUtils::RequestId> McpProtocolCancelledNotificationParams::requestId() const
{
    return mRequestId;
}

void McpProtocolCancelledNotificationParams::setRequestId(std::optional<McpProtocolUtils::RequestId> newRequestId)
{
    mRequestId = std::move(newRequestId);
}
