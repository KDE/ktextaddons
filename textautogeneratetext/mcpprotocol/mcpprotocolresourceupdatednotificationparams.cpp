/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolresourceupdatednotificationparams.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolResourceUpdatedNotificationParams::McpProtocolResourceUpdatedNotificationParams() = default;

McpProtocolResourceUpdatedNotificationParams::~McpProtocolResourceUpdatedNotificationParams() = default;

bool McpProtocolResourceUpdatedNotificationParams::operator==(const McpProtocolResourceUpdatedNotificationParams &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolResourceUpdatedNotificationParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "uri:" << t.uri();
    return d;
}

McpProtocolResourceUpdatedNotificationParams McpProtocolResourceUpdatedNotificationParams::fromJson(const QJsonObject &obj)
{
    McpProtocolResourceUpdatedNotificationParams prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
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
    mMeta = newMeta;
}

QString McpProtocolResourceUpdatedNotificationParams::uri() const
{
    return mUri;
}

void McpProtocolResourceUpdatedNotificationParams::setUri(const QString &newUri)
{
    mUri = newUri;
}
