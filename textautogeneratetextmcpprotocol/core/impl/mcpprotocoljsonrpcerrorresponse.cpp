/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoljsonrpcerrorresponse.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolJSONRPCErrorResponse::McpProtocolJSONRPCErrorResponse() = default;

bool McpProtocolJSONRPCErrorResponse::operator==(const McpProtocolJSONRPCErrorResponse &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolJSONRPCErrorResponse &t)
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
    if (const QJsonValue errorValue = obj.value("error"_L1); errorValue.isObject()) {
        response.setError(McpProtocolError::fromJson(errorValue.toObject()));
    }
    // id is null when server can't read request id (parse error)
    if (const QJsonValue idValue = obj.value("id"_L1); idValue.isString() || idValue.isDouble()) {
        response.setId(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::requestIdFromJson(idValue));
    }
    return response;
}

QJsonObject McpProtocolJSONRPCErrorResponse::toJson(const McpProtocolJSONRPCErrorResponse &response)
{
    QJsonObject obj;
    obj["error"_L1] = McpProtocolError::toJson(response.error());
    obj["jsonrpc"_L1] = u"2.0"_s;
    if (response.id().has_value()) {
        obj["id"_L1] = TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::requestIdToJson(*response.id());
    }
    return obj;
}

McpProtocolError McpProtocolJSONRPCErrorResponse::error() const
{
    return mError;
}

void McpProtocolJSONRPCErrorResponse::setError(McpProtocolError newError)
{
    mError = std::move(newError);
}

std::optional<McpProtocolUtils::RequestId> McpProtocolJSONRPCErrorResponse::id() const
{
    return mId;
}

void McpProtocolJSONRPCErrorResponse::setId(std::optional<McpProtocolUtils::RequestId> newId)
{
    mId = std::move(newId);
}
