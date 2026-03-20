/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolcancellednotificationparams.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QJsonObject>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolCancelledNotification
{
public:
    /*!
     */
    McpProtocolCancelledNotification();
    /*!
     */
    ~McpProtocolCancelledNotification();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolCancelledNotification &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolCancelledNotification fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolCancelledNotification &image);

    [[nodiscard]] McpProtocolCancelledNotificationParams params() const;
    void setParams(const McpProtocolCancelledNotificationParams &newParams);

private:
    McpProtocolCancelledNotificationParams mParams;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolCancelledNotification, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolCancelledNotification &t);
