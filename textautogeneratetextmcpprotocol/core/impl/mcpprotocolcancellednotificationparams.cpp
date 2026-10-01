/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcancellednotificationparams.h"
#include <QDebug>
#include <QJsonObject>
#include <utility>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolCancelledNotificationParams::McpProtocolCancelledNotificationParams() = default;

bool McpProtocolCancelledNotificationParams::operator==(const McpProtocolCancelledNotificationParams &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCancelledNotificationParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "reason:" << t.reason();
    d.space() << "requestId:" << t.requestId();
    return d;
}

McpProtocolCancelledNotificationParams McpProtocolCancelledNotificationParams::fromJson(const QJsonObject &obj)
{
    McpProtocolCancelledNotificationParams params;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        params.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    if (obj.contains("reason"_L1)) {
        params.setReason(obj.value("reason"_L1).toString());
    }
    if (obj.contains("requestId"_L1)) {
        params.setRequestId(McpProtocolUtils::requestIdFromJson(obj["requestId"_L1]));
    }
    return params;
}

QJsonObject McpProtocolCancelledNotificationParams::toJson(const McpProtocolCancelledNotificationParams &params)
{
    QJsonObject obj;
    if (params.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*params.meta());
    }
    if (params.reason().has_value()) {
        obj["reason"_L1] = *params.reason();
    }
    if (params.requestId().has_value()) {
        obj["requestId"_L1] = McpProtocolUtils::requestIdToJson(*params.requestId());
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
