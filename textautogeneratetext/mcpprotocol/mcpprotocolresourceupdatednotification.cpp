/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolresourceupdatednotification.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolResourceUpdatedNotification::McpProtocolResourceUpdatedNotification() = default;

McpProtocolResourceUpdatedNotification::~McpProtocolResourceUpdatedNotification() = default;

QByteArray McpProtocolResourceUpdatedNotification::type()
{
    return "notifications/resources/updated"_ba;
}

bool McpProtocolResourceUpdatedNotification::operator==(const McpProtocolResourceUpdatedNotification &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolResourceUpdatedNotification &t)
{
    d.space() << "param:" << t.params();
    return d;
}

McpProtocolResourceUpdatedNotification McpProtocolResourceUpdatedNotification::fromJson(const QJsonObject &obj)
{
    McpProtocolResourceUpdatedNotification prompt;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolResourceUpdatedNotification::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'method' must be 'notifications/tools/list_changed', got: " << obj.value("method"_L1).toString();
        return {};
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolResourceUpdatedNotificationParams::fromJson(obj["params"_L1].toObject()));
    }
    return prompt;
}

QJsonObject McpProtocolResourceUpdatedNotification::toJson(const McpProtocolResourceUpdatedNotification &boolean)
{
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolResourceUpdatedNotification::type());
    obj["params"_L1] = McpProtocolResourceUpdatedNotificationParams::toJson(boolean.params());
    return obj;
}

McpProtocolResourceUpdatedNotificationParams McpProtocolResourceUpdatedNotification::params() const
{
    return mParams;
}

void McpProtocolResourceUpdatedNotification::setParams(const McpProtocolResourceUpdatedNotificationParams &newParams)
{
    mParams = newParams;
}
