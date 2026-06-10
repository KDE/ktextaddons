/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoljsonrpcnotification.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolJSONRPCNotification::McpProtocolJSONRPCNotification() = default;

McpProtocolJSONRPCNotification::~McpProtocolJSONRPCNotification() = default;

bool McpProtocolJSONRPCNotification::operator==(const McpProtocolJSONRPCNotification &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolJSONRPCNotification &t)
{
    d.space() << "method:" << t.method();
    d.space() << "params:" << t.params();
    return d;
}

McpProtocolJSONRPCNotification McpProtocolJSONRPCNotification::fromJson(const QJsonObject &obj)
{
    McpProtocolJSONRPCNotification response;
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
    return response;
}

QJsonObject McpProtocolJSONRPCNotification::toJson(const McpProtocolJSONRPCNotification &boolean)
{
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
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

QString McpProtocolJSONRPCNotification::method() const
{
    return mMethod;
}

void McpProtocolJSONRPCNotification::setMethod(const QString &newMethod)
{
    mMethod = newMethod;
}

std::optional<QMap<QString, QJsonValue>> McpProtocolJSONRPCNotification::params() const
{
    return mParams;
}

void McpProtocolJSONRPCNotification::setParams(std::optional<QMap<QString, QJsonValue>> newParams)
{
    mParams = newParams;
}
