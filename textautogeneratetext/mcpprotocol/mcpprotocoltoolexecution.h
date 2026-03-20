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
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolToolExecution
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
    [[nodiscard]] TaskSupport taskSupport() const;
    /*!
     */
    void setTaskSupport(TaskSupport newTaskSupport);

    /*!
     */
    [[nodiscard]] static QString convertTaskSupportToString(McpProtocolToolExecution::TaskSupport mode);

private:
    TaskSupport mTaskSupport = TaskSupport::Unknown;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolToolExecution, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolToolExecution &t);
