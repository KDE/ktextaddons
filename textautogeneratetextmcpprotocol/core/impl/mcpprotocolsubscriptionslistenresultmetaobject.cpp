/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolsubscriptionslistenresultmetaobject.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSubscriptionsListenResultMetaObject::McpProtocolSubscriptionsListenResultMetaObject() = default;

bool McpProtocolSubscriptionsListenResultMetaObject::operator==(const McpProtocolSubscriptionsListenResultMetaObject &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscriptionsListenResultMetaObject &t)
{
    d.space() << "subscriptionId:" << t.subscriptionId();
    d.space() << "serverInfo:" << t.serverInfo();
    return d;
}

McpProtocolSubscriptionsListenResultMetaObject McpProtocolSubscriptionsListenResultMetaObject::fromJson(const QJsonObject &obj)
{
    McpProtocolSubscriptionsListenResultMetaObject metaObject;
    if (const QJsonValue subscriptionIdValue = obj.value("io.modelcontextprotocol/subscriptionId"_L1);
        McpProtocolUtils::isValidRequestId(subscriptionIdValue)) {
        metaObject.setSubscriptionId(McpProtocolUtils::requestIdFromJson(subscriptionIdValue));
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG)
            << "McpProtocolSubscriptionsListenResultMetaObject: missing required field 'io.modelcontextprotocol/subscriptionId'";
        return {};
    }
    if (const QJsonValue serverInfoValue = obj.value("io.modelcontextprotocol/serverInfo"_L1); serverInfoValue.isObject()) {
        McpProtocolImplementation serverInfo = McpProtocolImplementation::fromJson(serverInfoValue.toObject());
        if (serverInfo.isValid()) {
            metaObject.setServerInfo(std::move(serverInfo));
        } else {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG)
                << "McpProtocolSubscriptionsListenResultMetaObject: invalid field 'io.modelcontextprotocol/serverInfo'";
        }
    }
    return metaObject;
}

bool McpProtocolSubscriptionsListenResultMetaObject::isValid() const
{
    return mSubscriptionId.has_value();
}

QJsonObject McpProtocolSubscriptionsListenResultMetaObject::toJson(const McpProtocolSubscriptionsListenResultMetaObject &metaObject)
{
    QJsonObject obj;
    if (const auto subscriptionId = metaObject.subscriptionId(); subscriptionId.has_value()) {
        obj["io.modelcontextprotocol/subscriptionId"_L1] = McpProtocolUtils::requestIdToJson(*subscriptionId);
    }
    if (const auto serverInfo = metaObject.serverInfo(); serverInfo.has_value()) {
        obj["io.modelcontextprotocol/serverInfo"_L1] = McpProtocolImplementation::toJson(*serverInfo);
    }
    return obj;
}

std::optional<McpProtocolUtils::RequestId> McpProtocolSubscriptionsListenResultMetaObject::subscriptionId() const
{
    return mSubscriptionId;
}

void McpProtocolSubscriptionsListenResultMetaObject::setSubscriptionId(const std::optional<McpProtocolUtils::RequestId> &newSubscriptionId)
{
    mSubscriptionId = newSubscriptionId;
}

std::optional<McpProtocolImplementation> McpProtocolSubscriptionsListenResultMetaObject::serverInfo() const
{
    return mServerInfo;
}

void McpProtocolSubscriptionsListenResultMetaObject::setServerInfo(std::optional<McpProtocolImplementation> newServerInfo)
{
    mServerInfo = std::move(newServerInfo);
}
