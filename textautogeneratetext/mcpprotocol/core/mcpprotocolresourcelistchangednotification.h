/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolnotificationparams.h"
#include "mcpprotocolprompt.h"
#include "mcpprotocoltaskmetadata.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolResourceListChangedNotification
{
public:
    /*!
     */
    McpProtocolResourceListChangedNotification();
    /*!
     */
    ~McpProtocolResourceListChangedNotification();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolResourceListChangedNotification &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolResourceListChangedNotification fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolResourceListChangedNotification &image);

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
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceListChangedNotification, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d,
                                                             const TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceListChangedNotification &t);
