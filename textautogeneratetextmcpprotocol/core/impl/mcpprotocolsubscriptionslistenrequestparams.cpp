/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolsubscriptionslistenrequestparams.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSubscriptionsListenRequestParams::McpProtocolSubscriptionsListenRequestParams() = default;

bool McpProtocolSubscriptionsListenRequestParams::operator==(const McpProtocolSubscriptionsListenRequestParams &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscriptionsListenRequestParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "notifications:" << t.notifications();
    return d;
}

McpProtocolSubscriptionsListenRequestParams McpProtocolSubscriptionsListenRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolSubscriptionsListenRequestParams params;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        params.setMeta(McpProtocolSubscriptionsListenRequestParams::Meta::fromJson(metaValue.toObject()));
    }
    if (const QJsonValue notificationsValue = obj.value("notifications"_L1); notificationsValue.isObject()) {
        params.setNotifications(McpProtocolSubscriptionFilter::fromJson(notificationsValue.toObject()));
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolSubscriptionsListenRequestParams: missing required field 'notifications'";
        return {};
    }
    return params;
}

bool McpProtocolSubscriptionsListenRequestParams::isValid() const
{
    return mNotifications.has_value();
}

QJsonObject McpProtocolSubscriptionsListenRequestParams::toJson(const McpProtocolSubscriptionsListenRequestParams &subscriptionsListenRequestParams)
{
    QJsonObject obj;
    if (const auto notifications = subscriptionsListenRequestParams.notifications(); notifications.has_value()) {
        obj["notifications"_L1] = McpProtocolSubscriptionFilter::toJson(*notifications);
    }
    if (const auto meta = subscriptionsListenRequestParams.meta(); meta.has_value()) {
        obj["_meta"_L1] = McpProtocolSubscriptionsListenRequestParams::Meta::toJson(*meta);
    }
    return obj;
}

std::optional<McpProtocolSubscriptionsListenRequestParams::Meta> McpProtocolSubscriptionsListenRequestParams::meta() const
{
    return mMeta;
}

void McpProtocolSubscriptionsListenRequestParams::setMeta(std::optional<Meta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<McpProtocolSubscriptionFilter> McpProtocolSubscriptionsListenRequestParams::notifications() const
{
    return mNotifications;
}

void McpProtocolSubscriptionsListenRequestParams::setNotifications(std::optional<McpProtocolSubscriptionFilter> newNotifications)
{
    mNotifications = std::move(newNotifications);
}
