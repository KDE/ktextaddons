/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcanceltaskrequest.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolCancelTaskRequest::McpProtocolCancelTaskRequest() = default;

McpProtocolCancelTaskRequest::~McpProtocolCancelTaskRequest() = default;

QByteArray McpProtocolCancelTaskRequest::type()
{
    return "tasks/cancel"_ba;
}

bool McpProtocolCancelTaskRequest::Params::operator==(const McpProtocolCancelTaskRequest::Params &other) const = default;
bool McpProtocolCancelTaskRequest::operator==(const McpProtocolCancelTaskRequest &other) const = default;

McpProtocol::McpProtocolCancelTaskRequest::Params McpProtocol::McpProtocolCancelTaskRequest::Params::fromJson(const QJsonObject &obj)
{
    McpProtocol::McpProtocolCancelTaskRequest::Params params;
    params.setTaskId(obj.value("taskId"_L1).toString());
    return params;
}

QJsonObject McpProtocol::McpProtocolCancelTaskRequest::Params::toJson(const McpProtocol::McpProtocolCancelTaskRequest::Params &image)
{
    QJsonObject obj;
    obj["taskId"_L1] = image.taskId();
    return obj;
}

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolCancelTaskRequest::Params &t)
{
    d.space() << "taskId:" << t.taskId();
    return d;
}

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolCancelTaskRequest &t)
{
    d.space() << "params:" << t.params();
    d.space() << "id:" << t.id();
    return d;
}

McpProtocolCancelTaskRequest McpProtocolCancelTaskRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolCancelTaskRequest prompt;
    if (obj.contains("id"_L1)) {
        prompt.setId(McpProtocolUtils::requestIdFromJson(obj["id"_L1]));
    }
    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolCancelTaskRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'method' must be 'tasks/cancel', got: " << obj.value("method"_L1).toString();
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolCancelTaskRequest::Params::fromJson(obj["params"_L1].toObject()));
    }
    return prompt;
}

QJsonObject McpProtocolCancelTaskRequest::toJson(const McpProtocolCancelTaskRequest &boolean)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(boolean.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolCancelTaskRequest::type());
    obj["params"_L1] = McpProtocolCancelTaskRequest::Params::toJson(boolean.params());
    return obj;
}

McpProtocolCancelTaskRequest::Params McpProtocolCancelTaskRequest::params() const
{
    return mParams;
}

void McpProtocolCancelTaskRequest::setParams(const McpProtocolCancelTaskRequest::Params &newParams)
{
    mParams = newParams;
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
