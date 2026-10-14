/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolsubscriberequest.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSubscribeRequest::McpProtocolSubscribeRequest() = default;

QByteArray McpProtocolSubscribeRequest::type()
{
    return "resources/subscribe"_ba;
}

bool McpProtocolSubscribeRequest::operator==(const McpProtocolSubscribeRequest &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscribeRequest &t)
{
    d.space() << "params:" << t.params();
    d.space() << "id:" << t.id();
    return d;
}

McpProtocolSubscribeRequest McpProtocolSubscribeRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolSubscribeRequest prompt;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolSubscribeRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG)
            << "Field 'method' must be" << McpProtocolSubscribeRequest::type() << ", got:" << obj.value("method"_L1).toString();
        return {};
    }
    if (const QJsonValue paramsValue = obj.value("params"_L1); paramsValue.isObject()) {
        const McpProtocolSubscribeRequestParams params = McpProtocolSubscribeRequestParams::fromJson(paramsValue.toObject());
        if (!params.isValid()) {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolSubscribeRequest: invalid field 'params'";
            return {};
        }
        prompt.setParams(params);
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolSubscribeRequest: missing required field 'params'";
        return {};
    }
    if (const QJsonValue idValue = obj.value("id"_L1); idValue.isString() || idValue.isDouble()) {
        prompt.setId(McpProtocolUtils::requestIdFromJson(idValue));
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolSubscribeRequest: missing required field 'id'";
        return {};
    }
    return prompt;
}

QJsonObject McpProtocolSubscribeRequest::toJson(const McpProtocolSubscribeRequest &subscribeRequest)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(subscribeRequest.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolSubscribeRequest::type());
    obj["params"_L1] = McpProtocolSubscribeRequestParams::toJson(subscribeRequest.params());
    return obj;
}

McpProtocolUtils::RequestId McpProtocolSubscribeRequest::id() const
{
    return mId;
}

void McpProtocolSubscribeRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

McpProtocolSubscribeRequestParams McpProtocolSubscribeRequest::params() const
{
    return mParams;
}

void McpProtocolSubscribeRequest::setParams(const McpProtocolSubscribeRequestParams &newParams)
{
    mParams = newParams;
}
