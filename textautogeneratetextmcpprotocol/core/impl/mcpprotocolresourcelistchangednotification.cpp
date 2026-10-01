/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolresourcelistchangednotification.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolResourceListChangedNotification::McpProtocolResourceListChangedNotification() = default;

QByteArray McpProtocolResourceListChangedNotification::type()
{
    return "notifications/resources/list_changed"_ba;
}

bool McpProtocolResourceListChangedNotification::operator==(const McpProtocolResourceListChangedNotification &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceListChangedNotification &t)
{
    d.space() << "params:" << t.params();
    return d;
}

McpProtocolResourceListChangedNotification McpProtocolResourceListChangedNotification::fromJson(const QJsonObject &obj)
{
    McpProtocolResourceListChangedNotification prompt;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolResourceListChangedNotification::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG)
            << "Field 'method' must be" << McpProtocolResourceListChangedNotification::type() << ", got:" << obj.value("method"_L1).toString();
        return {};
    }
    if (const QJsonValue paramsValue = obj.value("params"_L1); paramsValue.isObject()) {
        prompt.setParams(McpProtocolNotificationParams::fromJson(paramsValue.toObject()));
    }
    return prompt;
}

QJsonObject McpProtocolResourceListChangedNotification::toJson(const McpProtocolResourceListChangedNotification &resourceListChangedNotification)
{
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolResourceListChangedNotification::type());
    if (resourceListChangedNotification.params().has_value()) {
        obj["params"_L1] = McpProtocolNotificationParams::toJson(*resourceListChangedNotification.params());
    }
    return obj;
}

std::optional<McpProtocolNotificationParams> McpProtocolResourceListChangedNotification::params() const
{
    return mParams;
}

void McpProtocolResourceListChangedNotification::setParams(std::optional<McpProtocolNotificationParams> newParams)
{
    mParams = std::move(newParams);
}
