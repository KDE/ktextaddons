/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltaskstatusnotification.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolTaskStatusNotification::McpProtocolTaskStatusNotification() = default;

McpProtocolTaskStatusNotification::~McpProtocolTaskStatusNotification() = default;

QByteArray McpProtocolTaskStatusNotification::type()
{
    return "notifications/tasks/status"_ba;
}

bool McpProtocolTaskStatusNotification::operator==(const McpProtocolTaskStatusNotification &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolTaskStatusNotification &t)
{
    d.space() << "params:" << t.params();
    return d;
}

McpProtocolTaskStatusNotification McpProtocolTaskStatusNotification::fromJson(const QJsonObject &obj)
{
    McpProtocolTaskStatusNotification prompt;
    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolTaskStatusNotification::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'method' must be 'notifications/tasks/status', got: " << obj.value("method"_L1).toString();
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolTaskStatusNotificationParams::fromJson(obj["params"_L1].toObject()));
    }
    return prompt;
}

QJsonObject McpProtocolTaskStatusNotification::toJson(const McpProtocolTaskStatusNotification &boolean)
{
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolTaskStatusNotification::type());
    obj["params"_L1] = McpProtocolTaskStatusNotificationParams::toJson(boolean.params());
    return obj;
}

McpProtocolTaskStatusNotificationParams McpProtocolTaskStatusNotification::params() const
{
    return mParams;
}

void McpProtocolTaskStatusNotification::setParams(const McpProtocolTaskStatusNotificationParams &newParams)
{
    mParams = newParams;
}
