/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltoollistchangednotification.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolToolListChangedNotification::McpProtocolToolListChangedNotification() = default;

McpProtocolToolListChangedNotification::~McpProtocolToolListChangedNotification() = default;

QByteArray McpProtocolToolListChangedNotification::type()
{
    return "notifications/tools/list_changed"_ba;
}

bool McpProtocolToolListChangedNotification::operator==(const McpProtocolToolListChangedNotification &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolToolListChangedNotification &t)
{
    d.space() << "params:" << t.params();
    return d;
}

McpProtocolToolListChangedNotification McpProtocolToolListChangedNotification::fromJson(const QJsonObject &obj)
{
    McpProtocolToolListChangedNotification prompt;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolToolListChangedNotification::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'method' must be 'notifications/tools/list_changed', got: " << obj.value("method"_L1).toString();
        return {};
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolNotificationParams::fromJson(obj["params"_L1].toObject()));
    }
    return prompt;
}

QJsonObject McpProtocolToolListChangedNotification::toJson(const McpProtocolToolListChangedNotification &boolean)
{
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolToolListChangedNotification::type());
    if (boolean.params().has_value()) {
        obj["params"_L1] = McpProtocolNotificationParams::toJson(*boolean.params());
    }
    return obj;
}

std::optional<McpProtocolNotificationParams> McpProtocolToolListChangedNotification::params() const
{
    return mParams;
}

void McpProtocolToolListChangedNotification::setParams(std::optional<McpProtocolNotificationParams> newParams)
{
    mParams = std::move(newParams);
}
