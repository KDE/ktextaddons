/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcancellednotification.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolCancelledNotification::McpProtocolCancelledNotification() = default;

McpProtocolCancelledNotification::~McpProtocolCancelledNotification() = default;

bool McpProtocolCancelledNotification::operator==(const McpProtocolCancelledNotification &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCancelledNotification &t)
{
    d.space() << "params:" << t.params();
    return d;
}

McpProtocolCancelledNotification McpProtocolCancelledNotification::fromJson(const QJsonObject &obj)
{
    McpProtocolCancelledNotification prompt;
    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != "notifications/cancelled"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'method' must be 'notifications/cancelled', got: " << obj.value("method"_L1).toString();
        return {};
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolCancelledNotificationParams::fromJson(obj["params"_L1].toObject()));
    }
    return prompt;
}

QJsonObject McpProtocolCancelledNotification::toJson(const McpProtocolCancelledNotification &boolean)
{
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = u"notifications/cancelled"_s;
    obj["params"_L1] = McpProtocolCancelledNotificationParams::toJson(boolean.params());
    return obj;
}

McpProtocolCancelledNotificationParams McpProtocolCancelledNotification::params() const
{
    return mParams;
}

void McpProtocolCancelledNotification::setParams(const McpProtocolCancelledNotificationParams &newParams)
{
    mParams = newParams;
}
