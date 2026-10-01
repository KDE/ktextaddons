/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolMeta>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
#include <optional>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolGetTaskResult
{
public:
    /*!
     */
    McpProtocolGetTaskResult();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolGetTaskResult &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolGetTaskResult fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolGetTaskResult &result);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

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
    [[nodiscard]] McpProtocolUtils::TaskStatus status() const;
    /*!
     */
    void setStatus(McpProtocolUtils::TaskStatus newStatus);

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
    std::optional<McpProtocolMeta> mMeta;
    QString mCreatedAt;
    QString mLastUpdatedAt;
    std::optional<qint64> mPollInterval;
    McpProtocolUtils::TaskStatus mStatus = McpProtocolUtils::TaskStatus::Unknown;
    std::optional<QString> mStatusMessage;
    QString mTaskId;
    std::optional<qint64> mTtl;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolGetTaskResult, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolGetTaskResult &t);
