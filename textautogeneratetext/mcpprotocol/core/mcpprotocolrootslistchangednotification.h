/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolnotificationparams.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QDebug;
class QJsonObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolRootsListChangedNotification
{
public:
    /*!
     */
    McpProtocolRootsListChangedNotification();
    /*!
     */
    ~McpProtocolRootsListChangedNotification();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolRootsListChangedNotification &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolRootsListChangedNotification fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolRootsListChangedNotification &image);

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
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolRootsListChangedNotification, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolRootsListChangedNotification &t);
