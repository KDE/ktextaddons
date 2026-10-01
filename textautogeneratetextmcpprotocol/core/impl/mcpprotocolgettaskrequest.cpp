/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolgettaskrequest.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolGetTaskRequest::McpProtocolGetTaskRequest() = default;

QByteArray McpProtocolGetTaskRequest::type()
{
    return "tasks/get"_ba;
}

bool McpProtocolGetTaskRequest::operator==(const McpProtocolGetTaskRequest &other) const = default;
bool McpProtocolGetTaskRequest::Params::operator==(const McpProtocolGetTaskRequest::Params &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolGetTaskRequest &t)
{
    d.space() << "id:" << t.id();
    d.space() << "params:" << t.params();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolGetTaskRequest::Params &t)
{
    d.space() << "taskId:" << t.taskId();
    return d;
}

McpProtocolGetTaskRequest::Params McpProtocolGetTaskRequest::Params::fromJson(const QJsonObject &obj)
{
    if (!obj.contains("taskId"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: taskId";
        return {};
    }
    McpProtocolGetTaskRequest::Params result;
    result.setTaskId(obj.value("taskId"_L1).toString());
    return result;
}

QJsonObject McpProtocolGetTaskRequest::Params::toJson(const McpProtocolGetTaskRequest::Params &params)
{
    QJsonObject obj;
    obj["taskId"_L1] = params.taskId();
    return obj;
}

McpProtocolGetTaskRequest McpProtocolGetTaskRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolGetTaskRequest request;
    if (obj.contains("id"_L1)) {
        request.setId(McpProtocolUtils::requestIdFromJson(obj["id"_L1]));
    }
    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolGetTaskRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG)
            << "McpProtocolGetTaskRequest: field 'method' must be" << McpProtocolGetTaskRequest::type() << "got:" << obj.value("method"_L1).toString();
        return {};
    }
    if (const QJsonValue paramsValue = obj.value("params"_L1); paramsValue.isObject()) {
        request.setParams(McpProtocolGetTaskRequest::Params::fromJson(paramsValue.toObject()));
    }
    return request;
}

QJsonObject McpProtocolGetTaskRequest::toJson(const McpProtocolGetTaskRequest &request)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(request.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolGetTaskRequest::type());
    obj["params"_L1] = McpProtocolGetTaskRequest::Params::toJson(request.params());
    return obj;
}

McpProtocolUtils::RequestId McpProtocolGetTaskRequest::id() const
{
    return mId;
}

void McpProtocolGetTaskRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

McpProtocolGetTaskRequest::Params McpProtocolGetTaskRequest::params() const
{
    return mParams;
}

void McpProtocolGetTaskRequest::setParams(Params newParams)
{
    mParams = std::move(newParams);
}

QString McpProtocolGetTaskRequest::Params::taskId() const
{
    return mTaskId;
}

void McpProtocolGetTaskRequest::Params::setTaskId(const QString &newTaskId)
{
    mTaskId = newTaskId;
}
