/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoldiscoverrequest.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolDiscoverRequest::McpProtocolDiscoverRequest() = default;

QByteArray McpProtocolDiscoverRequest::type()
{
    return "server/discover"_ba;
}

bool McpProtocolDiscoverRequest::operator==(const McpProtocolDiscoverRequest &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolDiscoverRequest &t)
{
    d.space() << "id:" << t.id();
    d.space() << "params:" << t.params();
    return d;
}

McpProtocolDiscoverRequest McpProtocolDiscoverRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolDiscoverRequest request;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolDiscoverRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG)
            << "Field 'method' must be" << McpProtocolDiscoverRequest::type() << ", got:" << obj.value("method"_L1).toString();
        return {};
    }
    const QJsonValue paramsValue = obj.value("params"_L1);
    if (!paramsValue.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolDiscoverRequest: missing required field 'params'";
        return {};
    }
    request.setParams(McpProtocolRequestParams::fromJson(paramsValue.toObject()));
    const QJsonValue idValue = obj.value("id"_L1);
    if (!idValue.isString() && !idValue.isDouble()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolDiscoverRequest: missing required field 'id'";
        return {};
    }
    request.setId(McpProtocolUtils::requestIdFromJson(idValue));
    return request;
}

QJsonObject McpProtocolDiscoverRequest::toJson(const McpProtocolDiscoverRequest &discoverRequest)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(discoverRequest.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolDiscoverRequest::type());
    obj["params"_L1] = McpProtocolRequestParams::toJson(discoverRequest.params());
    return obj;
}

McpProtocolUtils::RequestId McpProtocolDiscoverRequest::id() const
{
    return mId;
}

void McpProtocolDiscoverRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

McpProtocolRequestParams McpProtocolDiscoverRequest::params() const
{
    return mParams;
}

void McpProtocolDiscoverRequest::setParams(McpProtocolRequestParams newParams)
{
    mParams = std::move(newParams);
}
