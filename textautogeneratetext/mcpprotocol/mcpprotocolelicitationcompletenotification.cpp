/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolelicitationcompletenotification.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolElicitationCompleteNotification::McpProtocolElicitationCompleteNotification() = default;

McpProtocolElicitationCompleteNotification::~McpProtocolElicitationCompleteNotification() = default;

bool McpProtocolElicitationCompleteNotification::operator==(const McpProtocolElicitationCompleteNotification &other) const = default;

bool McpProtocolElicitationCompleteNotification::Params::operator==(const McpProtocolElicitationCompleteNotification::Params &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolElicitationCompleteNotification &t)
{
    return d;
}

McpProtocolElicitationCompleteNotification McpProtocolElicitationCompleteNotification::fromJson(const QJsonObject &obj)
{
    McpProtocolElicitationCompleteNotification prompt;
    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        co_return Utils::ResultError("Field 'jsonrpc' must be '2.0', got: " + obj.value("jsonrpc").toString());
    }
    if (obj.value("method").toString() != "notifications/elicitation/complete")
        co_return Utils::ResultError("Field 'method' must be 'notifications/elicitation/complete', got: " + obj.value("method").toString());
    if (obj.contains("params") && obj["params"].isObject())
        prompt._params = co_await fromJson<ElicitationCompleteNotification::Params>(obj["params"]);

    return prompt;
}

QJsonObject McpProtocolElicitationCompleteNotification::toJson(const McpProtocolElicitationCompleteNotification &boolean)
{
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1], u"notifications/elicitation/complete"_s;
    obj["params"_L1], toJson(boolean.params());

    return obj;
}

McpProtocolElicitationCompleteNotification::Params McpProtocolElicitationCompleteNotification::params() const
{
    return mParams;
}

void McpProtocolElicitationCompleteNotification::setParams(const Params &newParams)
{
    mParams = newParams;
}

McpProtocolElicitationCompleteNotification::Params &McpProtocolElicitationCompleteNotification::Params::elicitationId(const QString &v)
{
    mElicitationId = v;
    return *this;
}

const QString &McpProtocolElicitationCompleteNotification::Params::elicitationId() const
{
    return mElicitationId;
}
