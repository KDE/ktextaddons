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

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolCancelTaskRequest &t)
{
    return d;
}

McpProtocolCancelTaskRequest McpProtocolCancelTaskRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolCancelTaskRequest prompt;
    // TODO
    return prompt;
}

QJsonObject McpProtocolCancelTaskRequest::toJson(const McpProtocolCancelTaskRequest &boolean)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(boolean.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolCancelTaskRequest::type());
    // TODO obj["params"_L1] = McpProtocolCancelTaskRequest::Params::toJson(data._params);
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
