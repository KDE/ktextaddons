/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolnotificationparams.h"
#include "mcpprotocoltaskmetadata.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>

#include <QString>
class QDebug;
class QJsonObject;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolToolListChangedNotification
{
public:
    /*!
     */
    McpProtocolToolListChangedNotification();
    /*!
     */
    ~McpProtocolToolListChangedNotification();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolToolListChangedNotification &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolToolListChangedNotification fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolToolListChangedNotification &image);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolNotificationParams> params() const;
    /*!
     */
    void setParams(std::optional<McpProtocolNotificationParams> newParams);

private:
    std::optional<McpProtocolNotificationParams> mParams;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolToolListChangedNotification, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolToolListChangedNotification &t);
