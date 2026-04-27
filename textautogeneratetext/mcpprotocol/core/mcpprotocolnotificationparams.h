/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolmeta.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolNotificationParams
{
public:
    /*!
     */
    McpProtocolNotificationParams();
    /*!
     */
    ~McpProtocolNotificationParams();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolNotificationParams &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolNotificationParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolNotificationParams &image);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

private:
    std::optional<McpProtocolMeta> mMeta;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolNotificationParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolNotificationParams &t);
