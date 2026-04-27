/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoljsonrpcerrorresponse.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolJSONRPCErrorResponse::McpProtocolJSONRPCErrorResponse() = default;

McpProtocolJSONRPCErrorResponse::~McpProtocolJSONRPCErrorResponse() = default;

bool McpProtocolJSONRPCErrorResponse::operator==(const McpProtocolJSONRPCErrorResponse &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolJSONRPCErrorResponse &t)
{
    d.space() << "error:" << t.error();
    d.space() << "id:" << t.id();
    return d;
}

McpProtocolJSONRPCErrorResponse McpProtocolJSONRPCErrorResponse::fromJson(const QJsonObject &obj)
{
    McpProtocolJSONRPCErrorResponse response;
    if (obj.value("jsonrpc"_L1).toString() != u"2.0"_s) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.contains("error"_L1) && obj["error"_L1].isObject()) {
        response.setError(McpProtocolError::fromJson(obj["error"_L1].toObject()));
    }
    if (obj.contains("id"_L1)) {
        response.setId(McpProtocol::McpProtocolUtils::requestIdFromJson(obj["id"_L1]));
    }
    return response;
}

QJsonObject McpProtocolJSONRPCErrorResponse::toJson(const McpProtocolJSONRPCErrorResponse &boolean)
{
    QJsonObject obj;
    obj["error"_L1] = McpProtocolError::toJson(boolean.error());
    obj["jsonrpc"_L1] = u"2.0"_s;
    if (boolean.id().has_value()) {
        obj["id"_L1] = McpProtocol::McpProtocolUtils::requestIdToJson(*boolean.id());
    }
    return obj;
}

McpProtocolError McpProtocolJSONRPCErrorResponse::error() const
{
    return mError;
}

void McpProtocolJSONRPCErrorResponse::setError(const McpProtocolError &newError)
{
    mError = newError;
}

std::optional<McpProtocolUtils::RequestId> McpProtocolJSONRPCErrorResponse::id() const
{
    return mId;
}

void McpProtocolJSONRPCErrorResponse::setId(std::optional<McpProtocolUtils::RequestId> newId)
{
    mId = std::move(newId);
}
