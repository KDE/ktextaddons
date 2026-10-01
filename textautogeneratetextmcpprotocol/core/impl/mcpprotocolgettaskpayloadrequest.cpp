/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolgettaskpayloadrequest.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>
#include <utility>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolGetTaskPayloadRequest::McpProtocolGetTaskPayloadRequest() = default;

QByteArray McpProtocolGetTaskPayloadRequest::type()
{
    return "tasks/result"_ba;
}

bool McpProtocolGetTaskPayloadRequest::operator==(const McpProtocolGetTaskPayloadRequest &other) const = default;
bool McpProtocolGetTaskPayloadRequest::Params::operator==(const McpProtocolGetTaskPayloadRequest::Params &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolGetTaskPayloadRequest &t)
{
    d.space() << "id:" << t.id();
    d.space() << "params:" << t.params();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolGetTaskPayloadRequest::Params &t)
{
    d.space() << "taskId:" << t.taskId();
    return d;
}

McpProtocolGetTaskPayloadRequest::Params McpProtocolGetTaskPayloadRequest::Params::fromJson(const QJsonObject &obj)
{
    McpProtocolGetTaskPayloadRequest::Params params;
    params.setTaskId(obj.value("taskId"_L1).toString());
    return params;
}

QJsonObject McpProtocolGetTaskPayloadRequest::Params::toJson(const McpProtocolGetTaskPayloadRequest::Params &params)
{
    QJsonObject obj;
    obj["taskId"_L1] = params.taskId();
    return obj;
}

McpProtocolGetTaskPayloadRequest McpProtocolGetTaskPayloadRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolGetTaskPayloadRequest request;
    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolGetTaskPayloadRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolGetTaskPayloadRequest: field 'method' must be" << McpProtocolGetTaskPayloadRequest::type()
                                                       << "got:" << obj.value("method"_L1).toString();
        return {};
    }
    if (obj.contains("id"_L1)) {
        request.setId(McpProtocolUtils::requestIdFromJson(obj["id"_L1]));
    }
    if (const QJsonValue paramsValue = obj.value("params"_L1); paramsValue.isObject()) {
        request.setParams(McpProtocolGetTaskPayloadRequest::Params::fromJson(paramsValue.toObject()));
    }
    return request;
}

QJsonObject McpProtocolGetTaskPayloadRequest::toJson(const McpProtocolGetTaskPayloadRequest &request)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(request.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolGetTaskPayloadRequest::type());
    obj["params"_L1] = McpProtocolGetTaskPayloadRequest::Params::toJson(request.params());
    return obj;
}

McpProtocolUtils::RequestId McpProtocolGetTaskPayloadRequest::id() const
{
    return mId;
}

void McpProtocolGetTaskPayloadRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

McpProtocolGetTaskPayloadRequest::Params McpProtocolGetTaskPayloadRequest::params() const
{
    return mParams;
}

void McpProtocolGetTaskPayloadRequest::setParams(Params newParams)
{
    mParams = std::move(newParams);
}

QString McpProtocolGetTaskPayloadRequest::Params::taskId() const
{
    return mTaskId;
}

void McpProtocolGetTaskPayloadRequest::Params::setTaskId(const QString &newTaskId)
{
    mTaskId = newTaskId;
}
