/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolnotificationparams.h"
#include "mcpprotocolprompt.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolCancelTaskRequest
{
public:
    struct Params {
        QString mTaskId;

        [[nodiscard]] QString taskId() const;
        void setTaskId(const QString &newTaskId);
        [[nodiscard]] bool operator==(const McpProtocolCancelTaskRequest::Params &other) const;
        [[nodiscard]] static Params fromJson(const QJsonObject &obj);
        [[nodiscard]] static QJsonObject toJson(const Params &image);
    };
    /*!
     */
    McpProtocolCancelTaskRequest();
    /*!
     */
    ~McpProtocolCancelTaskRequest();

    /*!
     */
    [[nodiscard]] static QByteArray type();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolCancelTaskRequest &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolCancelTaskRequest fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolCancelTaskRequest &image);

    /*!
     */
    [[nodiscard]] McpProtocolCancelTaskRequest::Params params() const;
    /*!
     */
    void setParams(const McpProtocolCancelTaskRequest::Params &newParams);

    /*!
     */
    [[nodiscard]] McpProtocolUtils::RequestId id() const;
    /*!
     */
    void setId(const McpProtocolUtils::RequestId &newId);

private:
    McpProtocolUtils::RequestId mId;
    McpProtocolCancelTaskRequest::Params mParams;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolCancelTaskRequest, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCancelTaskRequest &t);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCancelTaskRequest::Params &t);
