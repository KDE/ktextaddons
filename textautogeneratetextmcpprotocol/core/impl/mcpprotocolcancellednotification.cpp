/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcancellednotification.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolCancelledNotification::McpProtocolCancelledNotification() = default;

QByteArray McpProtocolCancelledNotification::type()
{
    return "notifications/cancelled"_ba;
}

bool McpProtocolCancelledNotification::operator==(const McpProtocolCancelledNotification &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCancelledNotification &t)
{
    d.space() << "params:" << t.params();
    return d;
}

McpProtocolCancelledNotification McpProtocolCancelledNotification::fromJson(const QJsonObject &obj)
{
    McpProtocolCancelledNotification notification;
    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolCancelledNotification::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolCancelledNotification: field 'method' must be" << McpProtocolCancelledNotification::type()
                                                       << "got:" << obj.value("method"_L1).toString();
        return {};
    }
    if (const QJsonValue paramsValue = obj.value("params"_L1); paramsValue.isObject()) {
        notification.setParams(McpProtocolCancelledNotificationParams::fromJson(paramsValue.toObject()));
    }
    return notification;
}

QJsonObject McpProtocolCancelledNotification::toJson(const McpProtocolCancelledNotification &notification)
{
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolCancelledNotification::type());
    obj["params"_L1] = McpProtocolCancelledNotificationParams::toJson(notification.params());
    return obj;
}

McpProtocolCancelledNotificationParams McpProtocolCancelledNotification::params() const
{
    return mParams;
}

void McpProtocolCancelledNotification::setParams(McpProtocolCancelledNotificationParams newParams)
{
    mParams = std::move(newParams);
}
