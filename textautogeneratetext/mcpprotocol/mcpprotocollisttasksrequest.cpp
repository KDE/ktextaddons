/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocollisttasksrequest.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolListTasksRequest::McpProtocolListTasksRequest() = default;

McpProtocolListTasksRequest::~McpProtocolListTasksRequest() = default;

QByteArray McpProtocolListTasksRequest::type()
{
    return "tasks/list"_ba;
}

bool McpProtocolListTasksRequest::operator==(const McpProtocolListTasksRequest &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolListTasksRequest &t)
{
    d.space() << "params:" << t.params();
    d.space() << "id:" << t.id();
    return d;
}

McpProtocolListTasksRequest McpProtocolListTasksRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolListTasksRequest prompt;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolListTasksRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'method' must be 'notifications/progress', got: " << obj.value("method"_L1).toString();
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolPaginatedRequestParams::fromJson(obj["params"_L1].toObject()));
    }
    if (obj.contains("id"_L1)) {
        prompt.setId(McpProtocolUtils::requestIdFromJson(obj.value("id"_L1)));
    }
    return prompt;
}

QJsonObject McpProtocolListTasksRequest::toJson(const McpProtocolListTasksRequest &boolean)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(boolean.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolListTasksRequest::type());
    if (boolean.params().has_value()) {
        obj["params"_L1] = McpProtocolPaginatedRequestParams::toJson(*boolean.params());
    }
    return obj;
}

McpProtocolUtils::RequestId McpProtocolListTasksRequest::id() const
{
    return mId;
}

void McpProtocolListTasksRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

std::optional<McpProtocolPaginatedRequestParams> McpProtocolListTasksRequest::params() const
{
    return mParams;
}

void McpProtocolListTasksRequest::setParams(std::optional<McpProtocolPaginatedRequestParams> newParams)
{
    mParams = std::move(newParams);
}
