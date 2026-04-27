/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolpromptlistchangednotification.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolPromptListChangedNotification::McpProtocolPromptListChangedNotification() = default;

McpProtocolPromptListChangedNotification::~McpProtocolPromptListChangedNotification() = default;

QByteArray McpProtocolPromptListChangedNotification::type()
{
    return "notifications/prompts/list_changed"_ba;
}

bool McpProtocolPromptListChangedNotification::operator==(const McpProtocolPromptListChangedNotification &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolPromptListChangedNotification &t)
{
    d.space() << "params:" << t.params();
    return d;
}

McpProtocolPromptListChangedNotification McpProtocolPromptListChangedNotification::fromJson(const QJsonObject &obj)
{
    McpProtocolPromptListChangedNotification prompt;
    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolPromptListChangedNotification::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG)
            << "Field 'method' must be 'notifications/prompts/list_changed', got: " << obj.value("method"_L1).toString();
        return {};
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolNotificationParams::fromJson(obj["params"_L1].toObject()));
    }
    return prompt;
}

QJsonObject McpProtocolPromptListChangedNotification::toJson(const McpProtocolPromptListChangedNotification &boolean)
{
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolPromptListChangedNotification::type());
    if (boolean.params().has_value()) {
        obj["params"_L1] = McpProtocolNotificationParams::toJson(*boolean.params());
    }
    return obj;
}

std::optional<McpProtocolNotificationParams> McpProtocolPromptListChangedNotification::params() const
{
    return mParams;
}

void McpProtocolPromptListChangedNotification::setParams(std::optional<McpProtocolNotificationParams> newParams)
{
    mParams = newParams;
}
