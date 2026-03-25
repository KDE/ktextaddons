/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocollisttoolsrequest.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolListToolsRequest::McpProtocolListToolsRequest() = default;

McpProtocolListToolsRequest::~McpProtocolListToolsRequest() = default;

QByteArray McpProtocolListToolsRequest::type()
{
    return "tools/list"_ba;
}

bool McpProtocolListToolsRequest::operator==(const McpProtocolListToolsRequest &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolListToolsRequest &t)
{
    d.space() << "params:" << t.params();
    d.space() << "id:" << t.id();
    return d;
}

McpProtocolListToolsRequest McpProtocolListToolsRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolListToolsRequest prompt;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolListToolsRequest::type())) {
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

QJsonObject McpProtocolListToolsRequest::toJson(const McpProtocolListToolsRequest &boolean)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(boolean.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolListToolsRequest::type());
    if (boolean.params().has_value()) {
        obj["params"_L1] = McpProtocolPaginatedRequestParams::toJson(*boolean.params());
    }
    return obj;
}

McpProtocolUtils::RequestId McpProtocolListToolsRequest::id() const
{
    return mId;
}

void McpProtocolListToolsRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

std::optional<McpProtocolPaginatedRequestParams> McpProtocolListToolsRequest::params() const
{
    return mParams;
}

void McpProtocolListToolsRequest::setParams(std::optional<McpProtocolPaginatedRequestParams> newParams)
{
    mParams = std::move(newParams);
}
