/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolMeta>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolCancelTaskResult
{
public:
    /*!
     */
    McpProtocolCancelTaskResult();
    /*!
     */
    ~McpProtocolCancelTaskResult();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolCancelTaskResult &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolCancelTaskResult fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolCancelTaskResult &image);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

private:
    std::optional<McpProtocolMeta> mMeta;
    QString mCreatedAt;
    QString mLastUpdatedAt;
    std::optional<int> mPollInterval;
    McpProtocolUtils::TaskStatus _status;
    std::optional<QString> mStatusMessage;
    QString mTaskId;
    std::optional<int> mTtl;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolCancelTaskResult, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCancelTaskResult &t);
