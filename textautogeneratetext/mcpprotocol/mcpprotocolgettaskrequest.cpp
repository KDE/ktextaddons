/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolgettaskrequest.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolGetTaskRequest::McpProtocolGetTaskRequest() = default;

McpProtocolGetTaskRequest::~McpProtocolGetTaskRequest() = default;

QByteArray McpProtocolGetTaskRequest::type()
{
    return "tasks/get"_ba;
}

bool McpProtocolGetTaskRequest::operator==(const McpProtocolGetTaskRequest &other) const = default;
bool McpProtocolGetTaskRequest::Params::operator==(const McpProtocolGetTaskRequest::Params &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolGetTaskRequest &t)
{
    return d;
}

McpProtocolGetTaskRequest::Params McpProtocolGetTaskRequest::Params::fromJson(const QJsonObject &obj)
{
    if (!obj.contains("taskId"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Missing required field: taskId";
        return {};
    }
    McpProtocolGetTaskRequest::Params result;
    result.setTaskId(obj.value("taskId"_L1).toString());
    return result;
}

QJsonObject McpProtocolGetTaskRequest::Params::toJson(const McpProtocolGetTaskRequest::Params &image)
{
    QJsonObject obj;
    obj["taskId"_L1] = image.taskId();
    return obj;
}

McpProtocolGetTaskRequest McpProtocolGetTaskRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolGetTaskRequest prompt;
    if (obj.contains("id"_L1)) {
        prompt.setId(McpProtocolUtils::requestIdFromJson(obj["id"_L1]));
    }
    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolGetTaskRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'method' must be 'tasks/get', got: " << obj.value("method"_L1).toString();
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolGetTaskRequest::Params::fromJson(obj["params"_L1].toObject()));
    }
    return prompt;
}

QJsonObject McpProtocolGetTaskRequest::toJson(const McpProtocolGetTaskRequest &boolean)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(boolean.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolGetTaskRequest::type());
    obj["params"_L1] = McpProtocolGetTaskRequest::Params::toJson(boolean.params());
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

void McpProtocolGetTaskRequest::setParams(const Params &newParams)
{
    mParams = newParams;
}

QString McpProtocolGetTaskRequest::Params::taskId() const
{
    return mTaskId;
}

void McpProtocolGetTaskRequest::Params::setTaskId(const QString &newTaskId)
{
    mTaskId = newTaskId;
}
