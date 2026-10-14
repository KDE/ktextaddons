/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolreadresourcerequest.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolReadResourceRequest::McpProtocolReadResourceRequest() = default;

QByteArray McpProtocolReadResourceRequest::type()
{
    return "resources/read"_ba;
}

bool McpProtocolReadResourceRequest::operator==(const McpProtocolReadResourceRequest &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolReadResourceRequest &t)
{
    d.space() << "params:" << t.params();
    d.space() << "id:" << t.id();
    return d;
}

McpProtocolReadResourceRequest McpProtocolReadResourceRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolReadResourceRequest prompt;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolReadResourceRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG)
            << "Field 'method' must be" << McpProtocolReadResourceRequest::type() << ", got:" << obj.value("method"_L1).toString();
        return {};
    }
    if (const QJsonValue paramsValue = obj.value("params"_L1); paramsValue.isObject()) {
        const McpProtocolReadResourceRequestParams params = McpProtocolReadResourceRequestParams::fromJson(paramsValue.toObject());
        if (!params.isValid()) {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolReadResourceRequest: invalid field 'params'";
            return {};
        }
        prompt.setParams(params);
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolReadResourceRequest: missing required field 'params'";
        return {};
    }
    const QJsonValue idValue = obj.value("id"_L1);
    if (!idValue.isString() && !idValue.isDouble()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolReadResourceRequest: missing required field 'id'";
        return {};
    }
    prompt.setId(McpProtocolUtils::requestIdFromJson(idValue));
    return prompt;
}

QJsonObject McpProtocolReadResourceRequest::toJson(const McpProtocolReadResourceRequest &readResourceRequest)
{
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolReadResourceRequest::type());
    obj["params"_L1] = McpProtocolReadResourceRequestParams::toJson(readResourceRequest.params());
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(readResourceRequest.id());
    return obj;
}

McpProtocolUtils::RequestId McpProtocolReadResourceRequest::id() const
{
    return mId;
}

void McpProtocolReadResourceRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

McpProtocolReadResourceRequestParams McpProtocolReadResourceRequest::params() const
{
    return mParams;
}

void McpProtocolReadResourceRequest::setParams(const McpProtocolReadResourceRequestParams &newParams)
{
    mParams = newParams;
}
