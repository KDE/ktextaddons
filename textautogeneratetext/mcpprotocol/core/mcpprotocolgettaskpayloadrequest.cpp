/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolgettaskpayloadrequest.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolGetTaskPayloadRequest::McpProtocolGetTaskPayloadRequest() = default;

McpProtocolGetTaskPayloadRequest::~McpProtocolGetTaskPayloadRequest() = default;

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
    return {};
}

QJsonObject McpProtocolGetTaskPayloadRequest::Params::toJson(const McpProtocolGetTaskPayloadRequest::Params &image)
{
    QJsonObject obj;
    obj["taskId"_L1] = image.taskId();
    return obj;
}

McpProtocolGetTaskPayloadRequest McpProtocolGetTaskPayloadRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolGetTaskPayloadRequest prompt;
    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolGetTaskPayloadRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'method' must be 'tasks/result', got: " << obj.value("method"_L1).toString();
    }
    if (obj.contains("id"_L1)) {
        prompt.setId(McpProtocolUtils::requestIdFromJson(obj["id"_L1]));
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolGetTaskPayloadRequest::Params::fromJson(obj["params"_L1].toObject()));
    }
    return prompt;
}

QJsonObject McpProtocolGetTaskPayloadRequest::toJson(const McpProtocolGetTaskPayloadRequest &boolean)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(boolean.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolGetTaskPayloadRequest::type());
    obj["params"_L1] = McpProtocolGetTaskPayloadRequest::Params::toJson(boolean.params());
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

void McpProtocolGetTaskPayloadRequest::setParams(const Params &newParams)
{
    mParams = newParams;
}

QString McpProtocolGetTaskPayloadRequest::Params::taskId() const
{
    return mTaskId;
}

void McpProtocolGetTaskPayloadRequest::Params::setTaskId(const QString &newTaskId)
{
    mTaskId = newTaskId;
}
