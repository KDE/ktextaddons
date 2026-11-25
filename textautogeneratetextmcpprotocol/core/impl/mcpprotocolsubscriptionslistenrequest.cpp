/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolsubscriptionslistenrequest.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSubscriptionsListenRequest::McpProtocolSubscriptionsListenRequest() = default;

QByteArray McpProtocolSubscriptionsListenRequest::type()
{
    return "subscriptions/listen"_ba;
}

bool McpProtocolSubscriptionsListenRequest::operator==(const McpProtocolSubscriptionsListenRequest &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscriptionsListenRequest &t)
{
    d.space() << "id:" << t.id();
    d.space() << "params:" << t.params();
    return d;
}

McpProtocolSubscriptionsListenRequest McpProtocolSubscriptionsListenRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolSubscriptionsListenRequest request;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolSubscriptionsListenRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG)
            << "Field 'method' must be" << McpProtocolSubscriptionsListenRequest::type() << ", got:" << obj.value("method"_L1).toString();
        return {};
    }
    if (const QJsonValue paramsValue = obj.value("params"_L1); paramsValue.isObject()) {
        McpProtocolSubscriptionsListenRequestParams params = McpProtocolSubscriptionsListenRequestParams::fromJson(paramsValue.toObject());
        if (!params.isValid()) {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolSubscriptionsListenRequest: invalid field 'params'";
            return {};
        }
        request.setParams(std::move(params));
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolSubscriptionsListenRequest: missing required field 'params'";
        return {};
    }
    if (const QJsonValue idValue = obj.value("id"_L1); idValue.isString() || idValue.isDouble()) {
        request.setId(McpProtocolUtils::requestIdFromJson(idValue));
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolSubscriptionsListenRequest: missing required field 'id'";
        return {};
    }
    return request;
}

QJsonObject McpProtocolSubscriptionsListenRequest::toJson(const McpProtocolSubscriptionsListenRequest &subscriptionsListenRequest)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(subscriptionsListenRequest.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolSubscriptionsListenRequest::type());
    obj["params"_L1] = McpProtocolSubscriptionsListenRequestParams::toJson(subscriptionsListenRequest.params());
    return obj;
}

McpProtocolUtils::RequestId McpProtocolSubscriptionsListenRequest::id() const
{
    return mId;
}

void McpProtocolSubscriptionsListenRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

McpProtocolSubscriptionsListenRequestParams McpProtocolSubscriptionsListenRequest::params() const
{
    return mParams;
}

void McpProtocolSubscriptionsListenRequest::setParams(McpProtocolSubscriptionsListenRequestParams newParams)
{
    mParams = std::move(newParams);
}
