/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolprogressnotificationparams.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolProgressNotification
{
public:
    /*!
     */
    McpProtocolProgressNotification();
    /*!
     */
    ~McpProtocolProgressNotification();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolProgressNotification &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolProgressNotification fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolProgressNotification &image);

    /*!
     */
    [[nodiscard]] McpProtocolProgressNotificationParams params() const;
    /*!
     */
    void setParams(const McpProtocolProgressNotificationParams &newParams);

private:
    McpProtocolProgressNotificationParams mParams;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolProgressNotification, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolProgressNotification &t);
