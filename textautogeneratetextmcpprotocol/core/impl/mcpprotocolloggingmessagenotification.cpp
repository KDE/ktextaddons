/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolloggingmessagenotification.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolLoggingMessageNotification::McpProtocolLoggingMessageNotification() = default;

QByteArray McpProtocolLoggingMessageNotification::type()
{
    return "notifications/message"_ba;
}

bool McpProtocolLoggingMessageNotification::operator==(const McpProtocolLoggingMessageNotification &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolLoggingMessageNotification &t)
{
    d.space() << "params:" << t.params();
    return d;
}

McpProtocolLoggingMessageNotification McpProtocolLoggingMessageNotification::fromJson(const QJsonObject &obj)
{
    McpProtocolLoggingMessageNotification notification;
    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }

    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolLoggingMessageNotification::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolLoggingMessageNotification: field 'method' must be"
                                                       << McpProtocolLoggingMessageNotification::type() << "got:" << obj.value("method"_L1).toString();
        return {};
    }
    if (const QJsonValue paramsValue = obj.value("params"_L1); paramsValue.isObject()) {
        notification.setParams(McpProtocolLoggingMessageNotificationParams::fromJson(paramsValue.toObject()));
    }
    return notification;
}

QJsonObject McpProtocolLoggingMessageNotification::toJson(const McpProtocolLoggingMessageNotification &notification)
{
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolLoggingMessageNotification::type());
    obj["params"_L1] = McpProtocolLoggingMessageNotificationParams::toJson(notification.params());
    return obj;
}

McpProtocolLoggingMessageNotificationParams McpProtocolLoggingMessageNotification::params() const
{
    return mParams;
}

void McpProtocolLoggingMessageNotification::setParams(McpProtocolLoggingMessageNotificationParams newParams)
{
    mParams = std::move(newParams);
}
