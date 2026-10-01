/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolrootslistchangednotification.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolRootsListChangedNotification::McpProtocolRootsListChangedNotification() = default;

QByteArray McpProtocolRootsListChangedNotification::type()
{
    return "notifications/roots/list_changed"_ba;
}

bool McpProtocolRootsListChangedNotification::operator==(const McpProtocolRootsListChangedNotification &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolRootsListChangedNotification &t)
{
    d.space() << "params:" << t.params();
    return d;
}

McpProtocolRootsListChangedNotification McpProtocolRootsListChangedNotification::fromJson(const QJsonObject &obj)
{
    McpProtocolRootsListChangedNotification prompt;
    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolRootsListChangedNotification::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG)
            << "Field 'method' must be" << McpProtocolRootsListChangedNotification::type() << ", got:" << obj.value("method"_L1).toString();
        return {};
    }
    if (const QJsonValue paramsValue = obj.value("params"_L1); paramsValue.isObject()) {
        prompt.setParams(McpProtocolNotificationParams::fromJson(paramsValue.toObject()));
    }

    return prompt;
}

QJsonObject McpProtocolRootsListChangedNotification::toJson(const McpProtocolRootsListChangedNotification &rootsListChangedNotification)
{
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolRootsListChangedNotification::type());
    if (rootsListChangedNotification.params().has_value()) {
        obj["params"_L1] = McpProtocolNotificationParams::toJson(*rootsListChangedNotification.params());
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
