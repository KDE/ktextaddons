/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcanceltaskrequest.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolCancelTaskRequest::McpProtocolCancelTaskRequest() = default;

QByteArray McpProtocolCancelTaskRequest::type()
{
    return "tasks/cancel"_ba;
}

bool McpProtocolCancelTaskRequest::Params::operator==(const McpProtocolCancelTaskRequest::Params &other) const = default;
bool McpProtocolCancelTaskRequest::operator==(const McpProtocolCancelTaskRequest &other) const = default;

TextAutoGenerateTextMcpProtocolCore::McpProtocolCancelTaskRequest::Params
TextAutoGenerateTextMcpProtocolCore::McpProtocolCancelTaskRequest::Params::fromJson(const QJsonObject &obj)
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolCancelTaskRequest::Params params;
    params.setTaskId(obj.value("taskId"_L1).toString());
    return params;
}

QJsonObject TextAutoGenerateTextMcpProtocolCore::McpProtocolCancelTaskRequest::Params::toJson(
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolCancelTaskRequest::Params &params)
{
    QJsonObject obj;
    obj["taskId"_L1] = params.taskId();
    return obj;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCancelTaskRequest::Params &t)
{
    d.space() << "taskId:" << t.taskId();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCancelTaskRequest &t)
{
    d.space() << "params:" << t.params();
    d.space() << "id:" << t.id();
    return d;
}

McpProtocolCancelTaskRequest McpProtocolCancelTaskRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolCancelTaskRequest request;
    if (obj.contains("id"_L1)) {
        request.setId(McpProtocolUtils::requestIdFromJson(obj["id"_L1]));
    }
    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolCancelTaskRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG)
            << "McpProtocolCancelTaskRequest: field 'method' must be" << McpProtocolCancelTaskRequest::type() << "got:" << obj.value("method"_L1).toString();
        return {};
    }
    if (const QJsonValue paramsValue = obj.value("params"_L1); paramsValue.isObject()) {
        request.setParams(McpProtocolCancelTaskRequest::Params::fromJson(paramsValue.toObject()));
    }
    return request;
}

QJsonObject McpProtocolCancelTaskRequest::toJson(const McpProtocolCancelTaskRequest &request)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(request.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolCancelTaskRequest::type());
    obj["params"_L1] = McpProtocolCancelTaskRequest::Params::toJson(request.params());
    return obj;
}

McpProtocolCancelTaskRequest::Params McpProtocolCancelTaskRequest::params() const
{
    return mParams;
}

void McpProtocolCancelTaskRequest::setParams(McpProtocolCancelTaskRequest::Params newParams)
{
    mParams = std::move(newParams);
}

McpProtocolUtils::RequestId McpProtocolCancelTaskRequest::id() const
{
    return mId;
}

void McpProtocolCancelTaskRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

QString McpProtocolCancelTaskRequest::Params::taskId() const
{
    return mTaskId;
}

void McpProtocolCancelTaskRequest::Params::setTaskId(const QString &newTaskId)
{
    mTaskId = newTaskId;
}
