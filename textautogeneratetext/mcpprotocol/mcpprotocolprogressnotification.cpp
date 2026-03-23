/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolprogressnotification.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolProgressNotification::McpProtocolProgressNotification() = default;

McpProtocolProgressNotification::~McpProtocolProgressNotification() = default;

QByteArray McpProtocolProgressNotification::type()
{
    return "notifications/progress"_ba;
}

bool McpProtocolProgressNotification::operator==(const McpProtocolProgressNotification &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolProgressNotification &t)
{
    d.space() << "params:" << t.params();
    return d;
}

McpProtocolProgressNotification McpProtocolProgressNotification::fromJson(const QJsonObject &obj)
{
    McpProtocolProgressNotification prompt;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolProgressNotification::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'method' must be 'notifications/progress', got: " << obj.value("method"_L1).toString();
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolProgressNotificationParams::fromJson(obj["params"_L1].toObject()));
    }
    return prompt;
}

QJsonObject McpProtocolProgressNotification::toJson(const McpProtocolProgressNotification &boolean)
{
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolProgressNotification::type());
    obj["params"_L1] = McpProtocolProgressNotificationParams::toJson(boolean.params());
    return obj;
}

McpProtocolProgressNotificationParams McpProtocolProgressNotification::params() const
{
    return mParams;
}

void McpProtocolProgressNotification::setParams(const McpProtocolProgressNotificationParams &newParams)
{
    mParams = newParams;
}
