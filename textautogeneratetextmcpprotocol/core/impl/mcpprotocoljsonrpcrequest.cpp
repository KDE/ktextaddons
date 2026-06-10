/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoljsonrpcrequest.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolJSONRPCRequest::McpProtocolJSONRPCRequest() = default;

McpProtocolJSONRPCRequest::~McpProtocolJSONRPCRequest() = default;

bool McpProtocolJSONRPCRequest::operator==(const McpProtocolJSONRPCRequest &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolJSONRPCRequest &t)
{
    d.space() << "method:" << t.method();
    d.space() << "params:" << t.params();
    d.space() << "id:" << t.id();
    return d;
}

McpProtocolJSONRPCRequest McpProtocolJSONRPCRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolJSONRPCRequest response;
    if (!obj.contains("jsonrpc"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: jsonrpc";
        return {};
    }
    if (obj.value("jsonrpc"_L1).toString() != u"2.0"_s) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (!obj.contains("method"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: method";
        return {};
    }
    response.setMethod(obj.value("method"_L1).toString());
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        const QJsonObject mapObj_params = obj["params"_L1].toObject();
        QMap<QString, QJsonValue> map_params;
        for (auto it = mapObj_params.constBegin(); it != mapObj_params.constEnd(); ++it) {
            map_params.insert(it.key(), it.value());
        }
        response.setParams(map_params);
    }
    response.setId(McpProtocolUtils::requestIdFromJson(obj["id"_L1]));
    return response;
}

QJsonObject McpProtocolJSONRPCRequest::toJson(const McpProtocolJSONRPCRequest &boolean)
{
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(boolean.id());
    obj["method"_L1] = boolean.method();
    if (boolean.params().has_value()) {
        const auto params = *boolean.params();
        QJsonObject map_params;
        for (auto it = params.constBegin(); it != params.constEnd(); ++it) {
            map_params.insert(it.key(), it.value());
        }
        obj.insert("params"_L1, map_params);
    }
    return obj;
}

QString McpProtocolJSONRPCRequest::method() const
{
    return mMethod;
}

void McpProtocolJSONRPCRequest::setMethod(const QString &newMethod)
{
    mMethod = newMethod;
}

std::optional<QMap<QString, QJsonValue>> McpProtocolJSONRPCRequest::params() const
{
    return mParams;
}

void McpProtocolJSONRPCRequest::setParams(std::optional<QMap<QString, QJsonValue>> newParams)
{
    mParams = std::move(newParams);
}

McpProtocolUtils::RequestId McpProtocolJSONRPCRequest::id() const
{
    return mId;
}

void McpProtocolJSONRPCRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}
