/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolannotations.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QDebug;
class QJsonObject;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolToolExecution
{
    Q_GADGET
public:
    enum class TaskSupport : uint8_t {
        Unknown = 0,
        Forbidden,
        Optional,
        Required,
    };
    Q_ENUM(TaskSupport)

    /*!
     */
    McpProtocolToolExecution();
    /*!
     */
    ~McpProtocolToolExecution();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolToolExecution &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolToolExecution fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolToolExecution &image);

    /*!
     */
    [[nodiscard]] static QString convertTaskSupportToString(McpProtocolToolExecution::TaskSupport mode);
    /*!
     */
    [[nodiscard]] static McpProtocolToolExecution::TaskSupport convertTaskSupportFromString(const QString &str);

    /*!
     */
    [[nodiscard]] std::optional<TaskSupport> taskSupport() const;
    /*!
     */
    void setTaskSupport(std::optional<TaskSupport> newTaskSupport);

private:
    std::optional<TaskSupport> mTaskSupport;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolToolExecution, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolToolExecution &t);
