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
    static McpProtocolTask fromJson(const QJsonObject &obj);
    /*!
     */
    static QJsonObject toJson(const McpProtocolTask &image);

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
