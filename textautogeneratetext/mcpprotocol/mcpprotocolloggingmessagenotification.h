/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolannotations.h"
#include "mcpprotocolloggingmessagenotificationparams.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolLoggingMessageNotification
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
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolLoggingMessageNotification, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolLoggingMessageNotification &t);
