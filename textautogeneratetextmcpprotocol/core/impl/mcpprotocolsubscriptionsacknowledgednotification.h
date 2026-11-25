/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolSubscriptionsAcknowledgedNotificationParams>
class QDebug;
class QJsonObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolSubscriptionsAcknowledgedNotification
{
public:
    /*!
     */
    McpProtocolSubscriptionsAcknowledgedNotification();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolSubscriptionsAcknowledgedNotification &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolSubscriptionsAcknowledgedNotification fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolSubscriptionsAcknowledgedNotification &notification);

    /*!
     */
    [[nodiscard]] McpProtocolSubscriptionsAcknowledgedNotificationParams params() const;
    /*!
     */
    void setParams(McpProtocolSubscriptionsAcknowledgedNotificationParams newParams);

private:
    McpProtocolSubscriptionsAcknowledgedNotificationParams mParams;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscriptionsAcknowledgedNotification, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d,
                                                             const TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscriptionsAcknowledgedNotification &t);
