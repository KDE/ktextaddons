/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolRequestMeta>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolSubscriptionFilter>
#include <optional>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolSubscriptionsListenRequestParams
{
public:
    using Meta = McpProtocolRequestMeta;

    /*!
     */
    McpProtocolSubscriptionsListenRequestParams();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolSubscriptionsListenRequestParams &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolSubscriptionsListenRequestParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolSubscriptionsListenRequestParams &subscriptionsListenRequestParams);

    /*!
     * Returns true when the required field "notifications" is set.
     */
    [[nodiscard]] bool isValid() const;

    /*!
     */
    [[nodiscard]] std::optional<Meta> meta() const;
    /*!
     */
    void setMeta(std::optional<Meta> newMeta);

    /*!
     * The notifications the client opts in to on this stream (required).
     */
    [[nodiscard]] std::optional<McpProtocolSubscriptionFilter> notifications() const;
    /*!
     */
    void setNotifications(std::optional<McpProtocolSubscriptionFilter> newNotifications);

private:
    std::optional<Meta> mMeta;
    std::optional<McpProtocolSubscriptionFilter> mNotifications;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscriptionsListenRequestParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d,
                                                             const TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscriptionsListenRequestParams &t);
