/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolinitializednotification.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolInitializedNotification::McpProtocolInitializedNotification() = default;

McpProtocolInitializedNotification::~McpProtocolInitializedNotification() = default;

bool McpProtocolInitializedNotification::operator==(const McpProtocolInitializedNotification &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolInitializedNotification &t)
{
    d.space() << "params:" << t.params();
    return d;
}

McpProtocolInitializedNotification McpProtocolInitializedNotification::fromJson(const QJsonObject &obj)
{
    McpProtocolInitializedNotification prompt;
    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != "notifications/cancelled"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'method' must be 'notifications/cancelled', got: " << obj.value("method"_L1).toString();
        return {};
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolNotificationParams::fromJson(obj["params"_L1].toObject()));
    }

    return prompt;
}

QJsonObject McpProtocolInitializedNotification::toJson(const McpProtocolInitializedNotification &boolean)
{
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = u"notifications/initialized"_s;
    if (boolean.params().has_value()) {
        obj["params"_L1] = McpProtocolNotificationParams::toJson(*boolean.params());
    }
    return obj;
}

std::optional<McpProtocolNotificationParams> McpProtocolInitializedNotification::params() const
{
    return mParams;
}

void McpProtocolInitializedNotification::setParams(std::optional<McpProtocolNotificationParams> newParams)
{
    mParams = std::move(newParams);
}
