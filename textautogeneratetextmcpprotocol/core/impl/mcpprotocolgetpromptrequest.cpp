/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolgetpromptrequest.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolGetPromptRequest::McpProtocolGetPromptRequest() = default;

QByteArray McpProtocolGetPromptRequest::type()
{
    return "prompts/get"_ba;
}

bool McpProtocolGetPromptRequest::operator==(const McpProtocolGetPromptRequest &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolGetPromptRequest &t)
{
    d.space() << "params:" << t.params();
    d.space() << "id:" << t.id();
    return d;
}

McpProtocolGetPromptRequest McpProtocolGetPromptRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolGetPromptRequest request;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolGetPromptRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG)
            << "McpProtocolGetPromptRequest: field 'method' must be" << McpProtocolGetPromptRequest::type() << "got:" << obj.value("method"_L1).toString();
        return {};
    }
    if (const QJsonValue paramsValue = obj.value("params"_L1); paramsValue.isObject()) {
        request.setParams(McpProtocolGetPromptRequestParams::fromJson(paramsValue.toObject()));
    }
    if (obj.contains("id"_L1)) {
        request.setId(McpProtocolUtils::requestIdFromJson(obj.value("id"_L1)));
    }
    return request;
}

QJsonObject McpProtocolGetPromptRequest::toJson(const McpProtocolGetPromptRequest &request)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(request.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolGetPromptRequest::type());
    obj["params"_L1] = McpProtocolGetPromptRequestParams::toJson(request.params());
    return obj;
}

McpProtocolUtils::RequestId McpProtocolGetPromptRequest::id() const
{
    return mId;
}

void McpProtocolGetPromptRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

McpProtocolGetPromptRequestParams McpProtocolGetPromptRequest::params() const
{
    return mParams;
}

void McpProtocolGetPromptRequest::setParams(McpProtocolGetPromptRequestParams newParams)
{
    mParams = std::move(newParams);
}
