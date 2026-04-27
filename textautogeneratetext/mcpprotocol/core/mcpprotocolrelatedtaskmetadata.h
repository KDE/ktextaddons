/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolannotations.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolRelatedTaskMetadata
{
public:
    /*!
     */
    McpProtocolRelatedTaskMetadata();
    /*!
     */
    ~McpProtocolRelatedTaskMetadata();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolRelatedTaskMetadata &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolRelatedTaskMetadata fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolRelatedTaskMetadata &image);

    /*!
     */
    [[nodiscard]] QString taskId() const;
    /*!
     */
    void setTaskId(const QString &newTaskId);

private:
    QString mTaskId;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolRelatedTaskMetadata, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolRelatedTaskMetadata &t);
