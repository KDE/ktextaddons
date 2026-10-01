/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolelicitrequest.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolElicitRequest::McpProtocolElicitRequest() = default;

QByteArray McpProtocolElicitRequest::type()
{
    return "elicitation/create"_ba;
}

bool McpProtocolElicitRequest::operator==(const McpProtocolElicitRequest &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequest &t)
{
    d.space() << "params:" << McpProtocolUtils::elicitRequestParamsToJson(t.params());
    d.space() << "id:" << t.id();
    return d;
}

McpProtocolElicitRequest McpProtocolElicitRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolElicitRequest request;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolElicitRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG)
            << "McpProtocolElicitRequest: field 'method' must be" << McpProtocolElicitRequest::type() << "got:" << obj.value("method"_L1).toString();
        return {};
    }
    if (const QJsonValue paramsValue = obj.value("params"_L1); paramsValue.isObject()) {
        request.setParams(McpProtocolUtils::elicitRequestParamsFromJson(paramsValue));
    }
    if (obj.contains("id"_L1)) {
        request.setId(McpProtocolUtils::requestIdFromJson(obj.value("id"_L1)));
    }
    return request;
}

QJsonObject McpProtocolElicitRequest::toJson(const McpProtocolElicitRequest &request)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(request.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolElicitRequest::type());
    obj["params"_L1] = McpProtocolUtils::elicitRequestParamsToJson(request.params());
    return obj;
}

McpProtocolUtils::RequestId McpProtocolElicitRequest::id() const
{
    return mId;
}

void McpProtocolElicitRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

McpProtocolUtils::ElicitRequestParams McpProtocolElicitRequest::params() const
{
    return mParams;
}

void McpProtocolElicitRequest::setParams(McpProtocolUtils::ElicitRequestParams newParams)
{
    mParams = std::move(newParams);
}
