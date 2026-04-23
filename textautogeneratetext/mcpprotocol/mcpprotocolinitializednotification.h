/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolnotificationparams.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QString>
class QDebug;
class QJsonObject;

namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolInitializedNotification
{
public:
    /*!
     */
    McpProtocolInitializedNotification();
    /*!
     */
    ~McpProtocolInitializedNotification();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolInitializedNotification &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolInitializedNotification fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolInitializedNotification &image);

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
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolInitializedNotification, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolInitializedNotification &t);
