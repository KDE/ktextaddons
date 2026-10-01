/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolelicitationcompletenotification.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>
#include <utility>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolElicitationCompleteNotification::McpProtocolElicitationCompleteNotification() = default;

QByteArray McpProtocolElicitationCompleteNotification::type()
{
    return "notifications/elicitation/complete"_ba;
}

bool McpProtocolElicitationCompleteNotification::operator==(const McpProtocolElicitationCompleteNotification &other) const = default;

bool McpProtocolElicitationCompleteNotification::Params::operator==(const McpProtocolElicitationCompleteNotification::Params &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitationCompleteNotification &t)
{
    d.space() << "elicitationId:" << t.params().elicitationId();
    return d;
}

McpProtocolElicitationCompleteNotification::Params McpProtocolElicitationCompleteNotification::Params::fromJson(const QJsonObject &obj)
{
    McpProtocolElicitationCompleteNotification::Params result;
    result.setElicitationId(obj.value("elicitationId"_L1).toString());
    return result;
}

QJsonObject McpProtocolElicitationCompleteNotification::Params::toJson(const McpProtocolElicitationCompleteNotification::Params &params)
{
    QJsonObject obj;
    obj["elicitationId"_L1] = params.elicitationId();
    return obj;
}

McpProtocolElicitationCompleteNotification McpProtocolElicitationCompleteNotification::fromJson(const QJsonObject &obj)
{
    McpProtocolElicitationCompleteNotification notification;
    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolElicitationCompleteNotification::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolElicitationCompleteNotification: field 'method' must be"
                                                       << McpProtocolElicitationCompleteNotification::type() << "got:" << obj.value("method"_L1).toString();
        return {};
    }
    if (const QJsonValue paramsValue = obj.value("params"_L1); paramsValue.isObject()) {
        notification.setParams(McpProtocolElicitationCompleteNotification::Params::fromJson(paramsValue.toObject()));
    }

    return notification;
}

QJsonObject McpProtocolElicitationCompleteNotification::toJson(const McpProtocolElicitationCompleteNotification &notification)
{
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolElicitationCompleteNotification::type());
    obj["params"_L1] = McpProtocolElicitationCompleteNotification::Params::toJson(notification.params());
    return obj;
}

McpProtocolElicitationCompleteNotification::Params McpProtocolElicitationCompleteNotification::params() const
{
    return mParams;
}

void McpProtocolElicitationCompleteNotification::setParams(Params newParams)
{
    mParams = std::move(newParams);
}

const QString &McpProtocolElicitationCompleteNotification::Params::elicitationId() const
{
    return mElicitationId;
}

void McpProtocolElicitationCompleteNotification::Params::setElicitationId(const QString &newElicitationId)
{
    mElicitationId = newElicitationId;
}
