/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocollistresourcesrequest.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolListResourcesRequest::McpProtocolListResourcesRequest() = default;

QByteArray McpProtocolListResourcesRequest::type()
{
    return "resources/list"_ba;
}

bool McpProtocolListResourcesRequest::operator==(const McpProtocolListResourcesRequest &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolListResourcesRequest &t)
{
    d.space() << "params:" << t.params();
    d.space() << "id:" << t.id();
    return d;
}

McpProtocolListResourcesRequest McpProtocolListResourcesRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolListResourcesRequest request;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolListResourcesRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolListResourcesRequest: field 'method' must be" << McpProtocolListResourcesRequest::type()
                                                       << "got:" << obj.value("method"_L1).toString();
        return {};
    }
    if (const QJsonValue paramsValue = obj.value("params"_L1); paramsValue.isObject()) {
        request.setParams(McpProtocolPaginatedRequestParams::fromJson(paramsValue.toObject()));
    }
    if (obj.contains("id"_L1)) {
        request.setId(McpProtocolUtils::requestIdFromJson(obj.value("id"_L1)));
    }
    return request;
}

QJsonObject McpProtocolListResourcesRequest::toJson(const McpProtocolListResourcesRequest &request)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(request.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolListResourcesRequest::type());
    if (request.params().has_value()) {
        obj["params"_L1] = McpProtocolPaginatedRequestParams::toJson(*request.params());
    }
    return obj;
}

McpProtocolUtils::RequestId McpProtocolListResourcesRequest::id() const
{
    return mId;
}

void McpProtocolListResourcesRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

std::optional<McpProtocolPaginatedRequestParams> McpProtocolListResourcesRequest::params() const
{
    return mParams;
}

void McpProtocolListResourcesRequest::setParams(std::optional<McpProtocolPaginatedRequestParams> newParams)
{
    mParams = std::move(newParams);
}
