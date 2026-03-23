/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolgettaskpayloadrequest.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolGetTaskPayloadRequest::McpProtocolGetTaskPayloadRequest() = default;

McpProtocolGetTaskPayloadRequest::~McpProtocolGetTaskPayloadRequest() = default;

bool McpProtocolGetTaskPayloadRequest::operator==(const McpProtocolGetTaskPayloadRequest &other) const = default;
bool McpProtocolGetTaskPayloadRequest::Params::operator==(const McpProtocolGetTaskPayloadRequest::Params &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolGetTaskPayloadRequest &t)
{
    return d;
}

McpProtocolGetTaskPayloadRequest::Params McpProtocolGetTaskPayloadRequest::Params::fromJson(const QJsonObject &obj)
{
    return {};
}

QJsonObject McpProtocolGetTaskPayloadRequest::Params::toJson(const McpProtocolGetTaskPayloadRequest::Params &image)
{
    QJsonObject obj;
#if 0
    if (image.progressToken().has_value()) {
        obj.insert("progressToken", McpProtocolUtils::toJson(*image.progressToken()));
    }
#endif
    return obj;
}

McpProtocolGetTaskPayloadRequest McpProtocolGetTaskPayloadRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolGetTaskPayloadRequest prompt;
    // TODO
    return prompt;
}

QJsonObject McpProtocolGetTaskPayloadRequest::toJson(const McpProtocolGetTaskPayloadRequest &boolean)
{
    QJsonObject obj;
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
