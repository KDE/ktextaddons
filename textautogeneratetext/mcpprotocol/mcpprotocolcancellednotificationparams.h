/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolmeta.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolCancelledNotificationParams
{
public:
    /*!
     */
    McpProtocolCancelledNotificationParams();
    /*!
     */
    ~McpProtocolCancelledNotificationParams();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolCancelledNotificationParams &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolCancelledNotificationParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolCancelledNotificationParams &image);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

    /*!
     */
    [[nodiscard]] std::optional<QString> reason() const;
    /*!
     */
    void setReason(std::optional<QString> newReason);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolUtils::RequestId> requestId() const;
    /*!
     */
    void setRequestId(std::optional<McpProtocolUtils::RequestId> newRequestId);

private:
    std::optional<McpProtocolMeta> mMeta;
    std::optional<QString> mReason;
    std::optional<McpProtocolUtils::RequestId> mRequestId;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolCancelledNotificationParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolCancelledNotificationParams &t);
