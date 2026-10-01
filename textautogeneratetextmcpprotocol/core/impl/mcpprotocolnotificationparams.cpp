/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolnotificationparams.h"
#include <QDebug>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolNotificationParams::McpProtocolNotificationParams() = default;

bool McpProtocolNotificationParams::operator==(const McpProtocolNotificationParams &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolNotificationParams &t)
{
    d.space() << "meta:" << t.meta();
    return d;
}

McpProtocolNotificationParams McpProtocolNotificationParams::fromJson(const QJsonObject &obj)
{
    McpProtocolNotificationParams params;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        params.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    return params;
}

QJsonObject McpProtocolNotificationParams::toJson(const McpProtocolNotificationParams &params)
{
    QJsonObject obj;
    if (params.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*params.meta());
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
