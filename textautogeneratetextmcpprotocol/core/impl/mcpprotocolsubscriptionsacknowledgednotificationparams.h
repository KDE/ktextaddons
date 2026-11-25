/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolMeta>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolSubscriptionFilter>
#include <optional>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolSubscriptionsAcknowledgedNotificationParams
{
public:
    /*!
     */
    McpProtocolSubscriptionsAcknowledgedNotificationParams();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolSubscriptionsAcknowledgedNotificationParams &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolSubscriptionsAcknowledgedNotificationParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolSubscriptionsAcknowledgedNotificationParams &params);

    /*!
     * Returns true when the required field "notifications" is set.
     */
    [[nodiscard]] bool isValid() const;

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

    /*!
     * The subset of requested notification types the server agreed to honor (required).
     */
    [[nodiscard]] std::optional<McpProtocolSubscriptionFilter> notifications() const;
    /*!
     */
    void setNotifications(std::optional<McpProtocolSubscriptionFilter> newNotifications);

private:
    std::optional<McpProtocolMeta> mMeta;
    std::optional<McpProtocolSubscriptionFilter> mNotifications;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscriptionsAcknowledgedNotificationParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug
operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscriptionsAcknowledgedNotificationParams &t);
