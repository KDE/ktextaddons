/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolImplementation>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
#include <optional>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolSubscriptionsListenResultMetaObject
{
public:
    /*!
     */
    McpProtocolSubscriptionsListenResultMetaObject();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolSubscriptionsListenResultMetaObject &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolSubscriptionsListenResultMetaObject fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolSubscriptionsListenResultMetaObject &metaObject);

    /*!
     * Returns true when the required field "io.modelcontextprotocol/subscriptionId" is set.
     */
    [[nodiscard]] bool isValid() const;

    /*!
     * JSON-RPC ID of the subscriptions/listen request that opened the stream (required).
     */
    [[nodiscard]] std::optional<McpProtocolUtils::RequestId> subscriptionId() const;
    /*!
     */
    void setSubscriptionId(const std::optional<McpProtocolUtils::RequestId> &newSubscriptionId);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolImplementation> serverInfo() const;
    /*!
     */
    void setServerInfo(std::optional<McpProtocolImplementation> newServerInfo);

private:
    std::optional<McpProtocolUtils::RequestId> mSubscriptionId;
    std::optional<McpProtocolImplementation> mServerInfo;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscriptionsListenResultMetaObject, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d,
                                                             const TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscriptionsListenResultMetaObject &t);
