/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolmeta.h"
#include "mcpprotocoltask.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QDebug;
class QJsonObject;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolCreateTaskResult
{
public:
    /*!
     */
    McpProtocolCreateTaskResult();
    /*!
     */
    ~McpProtocolCreateTaskResult();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolCreateTaskResult &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolCreateTaskResult fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolCreateTaskResult &image);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

    /*!
     */
    [[nodiscard]] McpProtocolTask task() const;
    /*!
     */
    void setTask(const McpProtocolTask &newTask);

private:
    std::optional<McpProtocolMeta> mMeta;
    McpProtocolTask mTask;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolCreateTaskResult, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolCreateTaskResult &t);
