/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolannotations.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QJsonObject>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolLoggingMessageNotificationParams
{
    Q_GADGET
public:
    /*!
     */
    McpProtocolLoggingMessageNotificationParams();
    /*!
     */
    ~McpProtocolLoggingMessageNotificationParams();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolLoggingMessageNotificationParams &other) const;

    /*!
     */
    static McpProtocolLoggingMessageNotificationParams fromJson(const QJsonObject &obj);
    /*!
     */
    static QJsonObject toJson(const McpProtocolLoggingMessageNotificationParams &image);
    QString data() const;
    void setData(const QString &newData);

    McpProtocolUtils::LoggingLevel level() const;
    void setLevel(McpProtocolUtils::LoggingLevel newLevel);

    std::optional<QString> logger() const;
    void setLogger(std::optional<QString> newLogger);

private:
    // TODO missing _meta
    QString mData;
    McpProtocolUtils::LoggingLevel mLevel = McpProtocolUtils::LoggingLevel::Unknown;
    std::optional<QString> mLogger;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolLoggingMessageNotificationParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolLoggingMessageNotificationParams &t);
