/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocoltaskstatusnotificationparams.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;

class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolTaskStatusNotification
{
public:
    /*!
     */
    McpProtocolTaskStatusNotification();
    /*!
     */
    ~McpProtocolTaskStatusNotification();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolTaskStatusNotification &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolTaskStatusNotification fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolTaskStatusNotification &image);

    /*!
     */
    [[nodiscard]] McpProtocolTaskStatusNotificationParams params() const;
    /*!
     */
    void setParams(const McpProtocolTaskStatusNotificationParams &newParams);

private:
    McpProtocolTaskStatusNotificationParams mParams;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolTaskStatusNotification, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolTaskStatusNotification &t);
