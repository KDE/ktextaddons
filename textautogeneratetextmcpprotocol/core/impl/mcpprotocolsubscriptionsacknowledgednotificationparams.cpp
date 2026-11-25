/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolsubscriptionsacknowledgednotificationparams.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSubscriptionsAcknowledgedNotificationParams::McpProtocolSubscriptionsAcknowledgedNotificationParams() = default;

bool McpProtocolSubscriptionsAcknowledgedNotificationParams::operator==(const McpProtocolSubscriptionsAcknowledgedNotificationParams &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscriptionsAcknowledgedNotificationParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "notifications:" << t.notifications();
    return d;
}

McpProtocolSubscriptionsAcknowledgedNotificationParams McpProtocolSubscriptionsAcknowledgedNotificationParams::fromJson(const QJsonObject &obj)
{
    McpProtocolSubscriptionsAcknowledgedNotificationParams params;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        params.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    if (const QJsonValue notificationsValue = obj.value("notifications"_L1); notificationsValue.isObject()) {
        params.setNotifications(McpProtocolSubscriptionFilter::fromJson(notificationsValue.toObject()));
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolSubscriptionsAcknowledgedNotificationParams: missing required field 'notifications'";
        return {};
    }
    return params;
}

bool McpProtocolSubscriptionsAcknowledgedNotificationParams::isValid() const
{
    return mNotifications.has_value();
}

QJsonObject McpProtocolSubscriptionsAcknowledgedNotificationParams::toJson(const McpProtocolSubscriptionsAcknowledgedNotificationParams &params)
{
    QJsonObject obj;
    if (const auto meta = params.meta(); meta.has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*meta);
    }
    if (const auto notifications = params.notifications(); notifications.has_value()) {
        obj["notifications"_L1] = McpProtocolSubscriptionFilter::toJson(*notifications);
    }
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolSubscriptionsAcknowledgedNotificationParams::meta() const
{
    return mMeta;
}

void McpProtocolSubscriptionsAcknowledgedNotificationParams::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<McpProtocolSubscriptionFilter> McpProtocolSubscriptionsAcknowledgedNotificationParams::notifications() const
{
    return mNotifications;
}

void McpProtocolSubscriptionsAcknowledgedNotificationParams::setNotifications(std::optional<McpProtocolSubscriptionFilter> newNotifications)
{
    mNotifications = std::move(newNotifications);
}
