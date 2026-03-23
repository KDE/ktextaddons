/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolnotificationparams.h"
#include "mcpprotocolprompt.h"
#include "mcpprotocoltaskmetadata.h"
#include "textautogeneratetextmcpprotocol_export.h"
#include <QByteArray>
#include <QJsonObject>
#include <QString>
class QDebug;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolGetTaskRequest
{
public:
    struct Params {
        QString mTaskId;

        [[nodiscard]] bool operator==(const McpProtocolGetTaskRequest::Params &other) const;

        /*!
         */
        [[nodiscard]] static McpProtocolGetTaskRequest::Params fromJson(const QJsonObject &obj);
        /*!
         */
        [[nodiscard]] static QJsonObject toJson(const McpProtocolGetTaskRequest::Params &image);

        [[nodiscard]] QString taskId() const;
        void setTaskId(const QString &newTaskId);
    };

    /*!
     */
    McpProtocolGetTaskRequest();
    /*!
     */
    ~McpProtocolGetTaskRequest();

    [[nodiscard]] static QByteArray type();
    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolGetTaskRequest &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolGetTaskRequest fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolGetTaskRequest &image);

    /*!
     */
    [[nodiscard]] McpProtocolUtils::RequestId id() const;
    /*!
     */
    void setId(const McpProtocolUtils::RequestId &newId);

    /*!
     */
    [[nodiscard]] Params params() const;
    /*!
     */
    void setParams(const Params &newParams);

private:
    McpProtocolUtils::RequestId mId;
    Params mParams;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolGetTaskRequest, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolGetTaskRequest &t);
