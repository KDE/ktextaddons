/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolMeta>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTask>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolListTasksResult
{
public:
    /*!
     */
    McpProtocolListTasksResult();
    /*!
     */
    ~McpProtocolListTasksResult();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolListTasksResult &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolListTasksResult fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolListTasksResult &image);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

    /*!
     */
    [[nodiscard]] std::optional<QString> nextCursor() const;
    /*!
     */
    void setNextCursor(std::optional<QString> newNextCursor);

    /*!
     */
    [[nodiscard]] QList<McpProtocolTask> tasks() const;
    /*!
     */
    void setTasks(const QList<McpProtocolTask> &newTasks);

private:
    std::optional<McpProtocolMeta> mMeta;
    std::optional<QString> mNextCursor;
    QList<McpProtocolTask> mTasks;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolListTasksResult, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolListTasksResult &t);
