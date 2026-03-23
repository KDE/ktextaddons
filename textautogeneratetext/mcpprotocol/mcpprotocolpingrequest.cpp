/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolpingrequest.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolPingRequest::McpProtocolPingRequest() = default;

McpProtocolPingRequest::~McpProtocolPingRequest() = default;

QByteArray McpProtocolPingRequest::type()
{
    return "ping"_ba;
}

bool McpProtocolPingRequest::operator==(const McpProtocolPingRequest &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolPingRequest &t)
{
    d.space() << "params:" << t.params();
    // TODO id
    return d;
}

McpProtocolPingRequest McpProtocolPingRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolPingRequest prompt;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolPingRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'method' must be 'notifications/progress', got: " << obj.value("method"_L1).toString();
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolRequestParams::fromJson(obj["params"_L1].toObject()));
    }
    // TODO add id !
    return prompt;
}

QJsonObject McpProtocolPingRequest::toJson(const McpProtocolPingRequest &boolean)
{
    QJsonObject obj;
    // TODO obj["id"_L1] = toJsonValue(data._id)};
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolPingRequest::type());
    if (boolean.params().has_value()) {
        obj["params"_L1] = McpProtocolRequestParams::toJson(*boolean.params());
    }
    return obj;
}

McpProtocolUtils::RequestId McpProtocolPingRequest::id() const
{
    return mId;
}

void McpProtocolPingRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

std::optional<McpProtocolRequestParams> McpProtocolPingRequest::params() const
{
    return mParams;
}

void McpProtocolPingRequest::setParams(std::optional<McpProtocolRequestParams> newParams)
{
    mParams = std::move(newParams);
}
