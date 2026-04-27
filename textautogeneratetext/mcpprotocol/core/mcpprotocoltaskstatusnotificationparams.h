/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolnotificationparams.h"
#include "mcpprotocolprompt.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;

class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolTaskStatusNotificationParams
{
public:
    /*!
     */
    McpProtocolTaskStatusNotificationParams();
    /*!
     */
    ~McpProtocolTaskStatusNotificationParams();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolTaskStatusNotificationParams &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolTaskStatusNotificationParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolTaskStatusNotificationParams &image);

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
    [[nodiscard]] std::optional<int> pollInterval() const;
    /*!
     */
    void setPollInterval(std::optional<int> newPollInterval);

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
    [[nodiscard]] std::optional<int> ttl() const;
    /*!
     */
    void setTtl(std::optional<int> newTtl);

private:
    std::optional<McpProtocolMeta> mMeta;
    QString mCreatedAt;
    QString mLastUpdatedAt;
    std::optional<int> mPollInterval;
    McpProtocolUtils::TaskStatus mStatus = McpProtocolUtils::TaskStatus::Unknown;
    std::optional<QString> mStatusMessage;
    QString mTaskId;
    std::optional<int> mTtl;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolTaskStatusNotificationParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolTaskStatusNotificationParams &t);
