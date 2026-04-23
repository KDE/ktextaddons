/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolannotations.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QString>
class QDebug;
class QJsonObject;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolTask
{
public:
    /*!
     */
    McpProtocolTask();
    /*!
     */
    ~McpProtocolTask();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolTask &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolTask fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolTask &image);

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
    [[nodiscard]] McpProtocol::McpProtocolUtils::TaskStatus status() const;
    /*!
     */
    void setStatus(McpProtocol::McpProtocolUtils::TaskStatus newStatus);

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
    QString mCreatedAt;
    QString mLastUpdatedAt;
    std::optional<int> mPollInterval;
    McpProtocol::McpProtocolUtils::TaskStatus mStatus = McpProtocol::McpProtocolUtils::TaskStatus::Unknown;
    std::optional<QString> mStatusMessage;
    QString mTaskId;
    std::optional<int> mTtl;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolTask, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolTask &t);
