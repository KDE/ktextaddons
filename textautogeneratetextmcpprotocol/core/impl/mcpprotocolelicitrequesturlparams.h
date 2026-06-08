/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QDebug>
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTaskMetadata>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
class QJsonObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolElicitRequestURLParams
{
public:
    struct Meta {
        std::optional<McpProtocolUtils::ProgressToken> mProgressToken;

        [[nodiscard]] std::optional<McpProtocolUtils::ProgressToken> progressToken() const;
        void setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken);
        [[nodiscard]] bool operator==(const McpProtocolElicitRequestURLParams::Meta &other) const;

        /*!
         */
        [[nodiscard]] static McpProtocolElicitRequestURLParams::Meta fromJson(const QJsonObject &obj);
        /*!
         */
        [[nodiscard]] static QJsonObject toJson(const McpProtocolElicitRequestURLParams::Meta &image);
    };
    /*!
     */
    McpProtocolElicitRequestURLParams();
    /*!
     */
    ~McpProtocolElicitRequestURLParams();

    /*!
     */
    [[nodiscard]] std::optional<Meta> meta() const;
    /*!
     */
    void setMeta(std::optional<Meta> newMeta);

    /*!
     */
    [[nodiscard]] QString elicitationId() const;
    /*!
     */
    void setElicitationId(const QString &newElicitationId);

    /*!
     */
    [[nodiscard]] QString message() const;
    /*!
     */
    void setMessage(const QString &newMessage);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolTaskMetadata> task() const;
    /*!
     */
    void setTask(std::optional<McpProtocolTaskMetadata> newTask);

    /*!
     */
    [[nodiscard]] QString url() const;
    /*!
     */
    void setUrl(const QString &newUrl);

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolElicitRequestURLParams &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolElicitRequestURLParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolElicitRequestURLParams &image);

private:
    std::optional<Meta> mMeta;
    QString mElicitationId;
    QString mMessage;
    std::optional<McpProtocolTaskMetadata> mTask;
    QString mUrl;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams &t);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams::Meta &t);
