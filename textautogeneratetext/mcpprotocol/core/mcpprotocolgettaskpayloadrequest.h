/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolnotificationparams.h"
#include "mcpprotocolprompt.h"
#include "mcpprotocoltaskmetadata.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>

#include <QString>
class QDebug;
class QJsonObject;
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolGetTaskPayloadRequest
{
public:
    struct Params {
        QString mTaskId;

        [[nodiscard]] bool operator==(const McpProtocolGetTaskPayloadRequest::Params &other) const;

        /*!
         */
        [[nodiscard]] static McpProtocolGetTaskPayloadRequest::Params fromJson(const QJsonObject &obj);
        /*!
         */
        [[nodiscard]] static QJsonObject toJson(const McpProtocolGetTaskPayloadRequest::Params &image);

        [[nodiscard]] QString taskId() const;
        void setTaskId(const QString &newTaskId);
    };

    /*!
     */
    McpProtocolGetTaskPayloadRequest();
    /*!
     */
    ~McpProtocolGetTaskPayloadRequest();

    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolGetTaskPayloadRequest &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolGetTaskPayloadRequest fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolGetTaskPayloadRequest &image);

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
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolGetTaskPayloadRequest, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolGetTaskPayloadRequest &t);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolGetTaskPayloadRequest::Params &t);
