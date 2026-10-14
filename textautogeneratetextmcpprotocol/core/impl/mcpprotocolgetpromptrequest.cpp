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
    const QJsonValue idValue = obj.value("id"_L1);
    if (!McpProtocolUtils::isValidRequestId(idValue)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolGetPromptRequest: missing or invalid required field 'id'";
        return {};
    }
    request.setId(McpProtocolUtils::requestIdFromJson(idValue));
    const QJsonValue paramsValue = obj.value("params"_L1);
    if (!paramsValue.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolGetPromptRequest: missing required field 'params'";
        return {};
    }
    const McpProtocolGetPromptRequestParams params = McpProtocolGetPromptRequestParams::fromJson(paramsValue.toObject());
    if (!params.isValid()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolGetPromptRequest: invalid field 'params'";
        return {};
    }
    request.setParams(params);
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
