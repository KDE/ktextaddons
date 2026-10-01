/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolinitializednotification.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>
#include <utility>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolInitializedNotification::McpProtocolInitializedNotification() = default;

QByteArray McpProtocolInitializedNotification::type()
{
    return "notifications/initialized"_ba;
}

bool McpProtocolInitializedNotification::operator==(const McpProtocolInitializedNotification &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializedNotification &t)
{
    d.space() << "params:" << t.params();
    return d;
}

McpProtocolInitializedNotification McpProtocolInitializedNotification::fromJson(const QJsonObject &obj)
{
    McpProtocolInitializedNotification notification;
    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolInitializedNotification::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolInitializedNotification: field 'method' must be"
                                                       << McpProtocolInitializedNotification::type() << "got:" << obj.value("method"_L1).toString();
        return {};
    }
    if (const QJsonValue paramsValue = obj.value("params"_L1); paramsValue.isObject()) {
        notification.setParams(McpProtocolNotificationParams::fromJson(paramsValue.toObject()));
    }

    return notification;
}

QJsonObject McpProtocolInitializedNotification::toJson(const McpProtocolInitializedNotification &notification)
{
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolInitializedNotification::type());
    if (notification.params().has_value()) {
        obj["params"_L1] = McpProtocolNotificationParams::toJson(*notification.params());
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
