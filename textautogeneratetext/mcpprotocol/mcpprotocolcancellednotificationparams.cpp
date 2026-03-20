/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcancellednotificationparams.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolCancelledNotificationParams::McpProtocolCancelledNotificationParams() = default;

McpProtocolCancelledNotificationParams::~McpProtocolCancelledNotificationParams() = default;

bool McpProtocolCancelledNotificationParams::operator==(const McpProtocolCancelledNotificationParams &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolCancelledNotificationParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "reason:" << t.reason();
    // TODO d.space() << "requestId:" << t.requestId();
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
        // RODO result._requestId = co_await fromJson<RequestId>(obj["requestId"_L1]);
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
        // TODO obj.insert("requestId", toJsonValue(*boolean.requestId()));
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
