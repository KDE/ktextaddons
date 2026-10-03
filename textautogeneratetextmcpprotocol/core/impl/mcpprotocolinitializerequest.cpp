/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolinitializerequest.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolInitializeRequest::McpProtocolInitializeRequest() = default;

QByteArray McpProtocolInitializeRequest::type()
{
    return "initialize"_ba;
}

bool McpProtocolInitializeRequest::operator==(const McpProtocolInitializeRequest &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeRequest &t)
{
    d.space() << "params:" << t.params();
    d.space() << "id:" << t.id();
    return d;
}

McpProtocolInitializeRequest McpProtocolInitializeRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolInitializeRequest request;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolInitializeRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG)
            << "McpProtocolInitializeRequest: field 'method' must be" << McpProtocolInitializeRequest::type() << "got:" << obj.value("method"_L1).toString();
        return {};
    }
    if (const QJsonValue paramsValue = obj.value("params"_L1); paramsValue.isObject()) {
        request.setParams(McpProtocolInitializeRequestParams::fromJson(paramsValue.toObject()));
    }
    if (obj.contains("id"_L1)) {
        request.setId(McpProtocolUtils::requestIdFromJson(obj.value("id"_L1)));
    }
    return request;
}

QJsonObject McpProtocolInitializeRequest::toJson(const McpProtocolInitializeRequest &request)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(request.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolInitializeRequest::type());
    obj["params"_L1] = McpProtocolInitializeRequestParams::toJson(request.params());
    return obj;
}

McpProtocolUtils::RequestId McpProtocolInitializeRequest::id() const
{
    return mId;
}

void McpProtocolInitializeRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

McpProtocolInitializeRequestParams McpProtocolInitializeRequest::params() const
{
    return mParams;
}

void McpProtocolInitializeRequest::setParams(McpProtocolInitializeRequestParams newParams)
{
    mParams = std::move(newParams);
}
