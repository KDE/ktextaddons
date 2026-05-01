/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolresourcelistchangednotification.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>

#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolResourceListChangedNotification::McpProtocolResourceListChangedNotification() = default;

McpProtocolResourceListChangedNotification::~McpProtocolResourceListChangedNotification() = default;

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
            << "Field 'method' must be 'notifications/tools/list_changed', got: " << obj.value("method"_L1).toString();
        return {};
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolNotificationParams::fromJson(obj["params"_L1].toObject()));
    }
    return prompt;
}

QJsonObject McpProtocolResourceListChangedNotification::toJson(const McpProtocolResourceListChangedNotification &boolean)
{
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolResourceListChangedNotification::type());
    if (boolean.params().has_value()) {
        obj["params"_L1] = McpProtocolNotificationParams::toJson(*boolean.params());
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
