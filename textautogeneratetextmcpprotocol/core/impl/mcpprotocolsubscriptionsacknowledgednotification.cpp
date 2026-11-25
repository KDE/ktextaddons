/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolsubscriptionsacknowledgednotification.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSubscriptionsAcknowledgedNotification::McpProtocolSubscriptionsAcknowledgedNotification() = default;

QByteArray McpProtocolSubscriptionsAcknowledgedNotification::type()
{
    return "notifications/subscriptions/acknowledged"_ba;
}

bool McpProtocolSubscriptionsAcknowledgedNotification::operator==(const McpProtocolSubscriptionsAcknowledgedNotification &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscriptionsAcknowledgedNotification &t)
{
    d.space() << "params:" << t.params();
    return d;
}

McpProtocolSubscriptionsAcknowledgedNotification McpProtocolSubscriptionsAcknowledgedNotification::fromJson(const QJsonObject &obj)
{
    McpProtocolSubscriptionsAcknowledgedNotification notification;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolSubscriptionsAcknowledgedNotification::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG)
            << "Field 'method' must be" << McpProtocolSubscriptionsAcknowledgedNotification::type() << ", got:" << obj.value("method"_L1).toString();
        return {};
    }
    if (const QJsonValue paramsValue = obj.value("params"_L1); paramsValue.isObject()) {
        McpProtocolSubscriptionsAcknowledgedNotificationParams params =
            McpProtocolSubscriptionsAcknowledgedNotificationParams::fromJson(paramsValue.toObject());
        if (!params.isValid()) {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolSubscriptionsAcknowledgedNotification: invalid field 'params'";
            return {};
        }
        notification.setParams(std::move(params));
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolSubscriptionsAcknowledgedNotification: missing required field 'params'";
        return {};
    }
    return notification;
}

QJsonObject McpProtocolSubscriptionsAcknowledgedNotification::toJson(const McpProtocolSubscriptionsAcknowledgedNotification &notification)
{
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolSubscriptionsAcknowledgedNotification::type());
    obj["params"_L1] = McpProtocolSubscriptionsAcknowledgedNotificationParams::toJson(notification.params());
    return obj;
}

McpProtocolSubscriptionsAcknowledgedNotificationParams McpProtocolSubscriptionsAcknowledgedNotification::params() const
{
    return mParams;
}

void McpProtocolSubscriptionsAcknowledgedNotification::setParams(McpProtocolSubscriptionsAcknowledgedNotificationParams newParams)
{
    mParams = std::move(newParams);
}
