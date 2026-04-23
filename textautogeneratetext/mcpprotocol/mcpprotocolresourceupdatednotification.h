/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolnotificationparams.h"
#include "mcpprotocolprompt.h"
#include "mcpprotocolresourceupdatednotificationparams.h"
#include "mcpprotocoltaskmetadata.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QString>
class QDebug;
class QJsonObject;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolResourceUpdatedNotification
{
public:
    /*!
     */
    McpProtocolResourceUpdatedNotification();
    /*!
     */
    ~McpProtocolResourceUpdatedNotification();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolResourceUpdatedNotification &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolResourceUpdatedNotification fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolResourceUpdatedNotification &image);

    /*!
     */
    [[nodiscard]] McpProtocolResourceUpdatedNotificationParams params() const;
    /*!
     */
    void setParams(const McpProtocolResourceUpdatedNotificationParams &newParams);

private:
    McpProtocolResourceUpdatedNotificationParams mParams;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolResourceUpdatedNotification, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolResourceUpdatedNotification &t);
