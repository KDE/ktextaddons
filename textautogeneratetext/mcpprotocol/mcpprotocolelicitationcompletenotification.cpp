/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolelicitationcompletenotification.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolElicitationCompleteNotification::McpProtocolElicitationCompleteNotification() = default;

McpProtocolElicitationCompleteNotification::~McpProtocolElicitationCompleteNotification() = default;

QByteArray McpProtocolElicitationCompleteNotification::type()
{
    return "notifications/elicitation/complete"_ba;
}

bool McpProtocolElicitationCompleteNotification::operator==(const McpProtocolElicitationCompleteNotification &other) const = default;

bool McpProtocolElicitationCompleteNotification::Params::operator==(const McpProtocolElicitationCompleteNotification::Params &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolElicitationCompleteNotification &t)
{
    d.space() << " params" << t.params().elicitationId();
    return d;
}

McpProtocolElicitationCompleteNotification::Params McpProtocolElicitationCompleteNotification::Params::fromJson(const QJsonObject &obj)
{
    McpProtocolElicitationCompleteNotification::Params result;
    result.mElicitationId = obj.value("elicitationId"_L1).toString();
    return result;
}

QJsonObject McpProtocolElicitationCompleteNotification::Params::toJson(const McpProtocolElicitationCompleteNotification::Params &image)
{
    QJsonObject obj;
    obj["elicitationId"_L1] = image.mElicitationId;
    return obj;
}

McpProtocolElicitationCompleteNotification McpProtocolElicitationCompleteNotification::fromJson(const QJsonObject &obj)
{
    McpProtocolElicitationCompleteNotification prompt;
    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolElicitationCompleteNotification::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'method' must be 'notifications/elicitation/complete', got: " << obj.value("method"_L1).toString();
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolElicitationCompleteNotification::Params::fromJson(obj["params"_L1].toObject()));
    }

    return prompt;
}

QJsonObject McpProtocolElicitationCompleteNotification::toJson(const McpProtocolElicitationCompleteNotification &boolean)
{
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolElicitationCompleteNotification::type());
    obj["params"_L1] = McpProtocolElicitationCompleteNotification::Params::toJson(boolean.params());
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
