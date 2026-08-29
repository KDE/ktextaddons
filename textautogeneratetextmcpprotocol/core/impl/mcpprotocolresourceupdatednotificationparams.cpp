/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolresourceupdatednotificationparams.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolResourceUpdatedNotificationParams::McpProtocolResourceUpdatedNotificationParams() = default;

bool McpProtocolResourceUpdatedNotificationParams::operator==(const McpProtocolResourceUpdatedNotificationParams &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceUpdatedNotificationParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "uri:" << t.uri();
    return d;
}

McpProtocolResourceUpdatedNotificationParams McpProtocolResourceUpdatedNotificationParams::fromJson(const QJsonObject &obj)
{
    McpProtocolResourceUpdatedNotificationParams prompt;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    prompt.setUri(obj.value("uri"_L1).toString());
    return prompt;
}

QJsonObject McpProtocolResourceUpdatedNotificationParams::toJson(const McpProtocolResourceUpdatedNotificationParams &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    obj["uri"_L1] = boolean.uri();
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolResourceUpdatedNotificationParams::meta() const
{
    return mMeta;
}

void McpProtocolResourceUpdatedNotificationParams::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

QString McpProtocolResourceUpdatedNotificationParams::uri() const
{
    return mUri;
}

void McpProtocolResourceUpdatedNotificationParams::setUri(const QString &newUri)
{
    mUri = newUri;
}
