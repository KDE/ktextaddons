/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
#include <optional>
class QDebug;
class QJsonObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolTask
{
public:
    /*!
     */
    McpProtocolTask();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolTask &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolTask fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolTask &task);

    /*!
     */
    [[nodiscard]] QString createdAt() const;
    /*!
     */
    void setCreatedAt(const QString &newCreatedAt);

    /*!
     */
    [[nodiscard]] QString lastUpdatedAt() const;
    /*!
     */
    void setLastUpdatedAt(const QString &newLastUpdatedAt);

    /*!
     */
    [[nodiscard]] std::optional<qint64> pollInterval() const;
    /*!
     */
    void setPollInterval(std::optional<qint64> newPollInterval);

    /*!
     */
    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::TaskStatus status() const;
    /*!
     */
    void setStatus(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::TaskStatus newStatus);

    /*!
     */
    [[nodiscard]] std::optional<QString> statusMessage() const;
    /*!
     */
    void setStatusMessage(std::optional<QString> newStatusMessage);

    /*!
     */
    [[nodiscard]] QString taskId() const;
    /*!
     */
    void setTaskId(const QString &newTaskId);

    /*!
     */
    [[nodiscard]] std::optional<qint64> ttl() const;
    /*!
     */
    void setTtl(std::optional<qint64> newTtl);

private:
    QString mCreatedAt;
    QString mLastUpdatedAt;
    std::optional<qint64> mPollInterval;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::TaskStatus mStatus = TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::TaskStatus::Unknown;
    std::optional<QString> mStatusMessage;
    QString mTaskId;
    std::optional<qint64> mTtl;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolTask, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolTask &t);
