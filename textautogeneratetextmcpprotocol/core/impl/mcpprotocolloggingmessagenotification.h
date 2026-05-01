/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolannotations.h"
#include "mcpprotocolloggingmessagenotificationparams.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QString>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolLoggingMessageNotification
{
public:
    /*!
     */
    McpProtocolLoggingMessageNotification();
    /*!
     */
    ~McpProtocolLoggingMessageNotification();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolLoggingMessageNotification &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolLoggingMessageNotification fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolLoggingMessageNotification &image);

    /*!
     */
    [[nodiscard]] McpProtocolLoggingMessageNotificationParams params() const;
    /*!
     */
    void setParams(const McpProtocolLoggingMessageNotificationParams &newParams);

private:
    McpProtocolLoggingMessageNotificationParams mParams;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolLoggingMessageNotification, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolLoggingMessageNotification &t);
