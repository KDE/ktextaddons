/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcalltoolrequest.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolCallToolRequest::McpProtocolCallToolRequest() = default;

QByteArray McpProtocolCallToolRequest::type()
{
    return "tools/call"_ba;
}

bool McpProtocolCallToolRequest::operator==(const McpProtocolCallToolRequest &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCallToolRequest &t)
{
    d.space() << "id:" << t.id();
    d.space() << "params:" << t.params();
    return d;
}

McpProtocolCallToolRequest McpProtocolCallToolRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolCallToolRequest request;
    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolCallToolRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG)
            << "McpProtocolCallToolRequest: field 'method' must be" << McpProtocolCallToolRequest::type() << "got:" << obj.value("method"_L1).toString();
        return {};
    }
    if (obj.contains("id"_L1)) {
        request.setId(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::requestIdFromJson(obj["id"_L1]));
    }
    if (const QJsonValue paramsValue = obj.value("params"_L1); paramsValue.isObject()) {
        request.setParams(McpProtocolCallToolRequestParams::fromJson(paramsValue.toObject()));
    }
    return request;
}

QJsonObject McpProtocolCallToolRequest::toJson(const McpProtocolCallToolRequest &request)
{
    QJsonObject obj;
    obj["id"_L1] = TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::requestIdToJson(request.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolCallToolRequest::type());
    obj["params"_L1] = McpProtocolCallToolRequestParams::toJson(request.params());
    return obj;
}

McpProtocolUtils::RequestId McpProtocolCallToolRequest::id() const
{
    return mId;
}

void McpProtocolCallToolRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

McpProtocolCallToolRequestParams McpProtocolCallToolRequest::params() const
{
    return mParams;
}

void McpProtocolCallToolRequest::setParams(McpProtocolCallToolRequestParams newParams)
{
    mParams = std::move(newParams);
}
