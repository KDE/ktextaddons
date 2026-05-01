/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolannotations.h"
#include "mcpprotocolmeta.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QString>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolLoggingMessageNotificationParams
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
    [[nodiscard]] static McpProtocolLoggingMessageNotificationParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolLoggingMessageNotificationParams &image);
    /*!
     */
    [[nodiscard]] QString data() const;
    /*!
     */
    void setData(const QString &newData);

    /*!
     */
    [[nodiscard]] McpProtocolUtils::LoggingLevel level() const;
    /*!
     */
    void setLevel(McpProtocolUtils::LoggingLevel newLevel);

    /*!
     */
    [[nodiscard]] std::optional<QString> logger() const;
    /*!
     */
    void setLogger(std::optional<QString> newLogger);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

private:
    std::optional<McpProtocolMeta> mMeta;
    QString mData;
    McpProtocolUtils::LoggingLevel mLevel = McpProtocolUtils::LoggingLevel::Unknown;
    std::optional<QString> mLogger;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolLoggingMessageNotificationParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d,
                                                             const TextAutoGenerateTextMcpProtocolCore::McpProtocolLoggingMessageNotificationParams &t);
