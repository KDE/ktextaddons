/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolrootslistchangednotification.h"
#include "textautogeneratetextmcpprotocol_debug.h"
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolRootsListChangedNotification::McpProtocolRootsListChangedNotification() = default;

McpProtocolRootsListChangedNotification::~McpProtocolRootsListChangedNotification() = default;

bool McpProtocolRootsListChangedNotification::operator==(const McpProtocolRootsListChangedNotification &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolRootsListChangedNotification &t)
{
    d.space() << "params:" << t.params();
    return d;
}

McpProtocolRootsListChangedNotification McpProtocolRootsListChangedNotification::fromJson(const QJsonObject &obj)
{
    McpProtocolRootsListChangedNotification prompt;
    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != "notifications/roots/list_changed"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'method' must be 'notifications/roots/list_changed', got: " << obj.value("method"_L1).toString();
        return {};
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolNotificationParams::fromJson(obj["params"_L1].toObject()));
    }

    return prompt;
}

QJsonObject McpProtocolRootsListChangedNotification::toJson(const McpProtocolRootsListChangedNotification &boolean)
{
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = u"notifications/roots/list_changed"_s;
    if (boolean.params().has_value()) {
        obj["params"_L1] = McpProtocolNotificationParams::toJson(*boolean.params());
    }
    return obj;
}

std::optional<McpProtocolNotificationParams> McpProtocolRootsListChangedNotification::params() const
{
    return mParams;
}

void McpProtocolRootsListChangedNotification::setParams(std::optional<McpProtocolNotificationParams> newParams)
{
    mParams = std::move(newParams);
}
