/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolloggingmessagenotification.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolLoggingMessageNotification::McpProtocolLoggingMessageNotification() = default;

McpProtocolLoggingMessageNotification::~McpProtocolLoggingMessageNotification() = default;

bool McpProtocolLoggingMessageNotification::operator==(const McpProtocolLoggingMessageNotification &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolLoggingMessageNotification &t)
{
    d.space() << "params:" << t.params();
    return d;
}

McpProtocolLoggingMessageNotification McpProtocolLoggingMessageNotification::fromJson(const QJsonObject &obj)
{
    McpProtocolLoggingMessageNotification prompt;
    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }

    if (obj.value("method"_L1).toString() != "notifications/message"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'method' must be 'notifications/message', got: " << obj.value("method"_L1).toString();
        return {};
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolLoggingMessageNotificationParams::fromJson(obj["params"_L1].toObject()));
    }
    return prompt;
}

QJsonObject McpProtocolLoggingMessageNotification::toJson(const McpProtocolLoggingMessageNotification &boolean)
{
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = u"notifications/message"_s;
    obj["params"_L1] = McpProtocolLoggingMessageNotificationParams::toJson(boolean.params());
    return obj;
}

McpProtocolLoggingMessageNotificationParams McpProtocolLoggingMessageNotification::params() const
{
    return mParams;
}

void McpProtocolLoggingMessageNotification::setParams(const McpProtocolLoggingMessageNotificationParams &newParams)
{
    mParams = newParams;
}
