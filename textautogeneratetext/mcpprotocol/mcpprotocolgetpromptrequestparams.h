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
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolGetPromptRequestParams
{
public:
    struct Meta {
        std::optional<McpProtocolUtils::ProgressToken> mProgressToken;

        [[nodiscard]] std::optional<McpProtocolUtils::ProgressToken> progressToken() const;
        void setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken);
        [[nodiscard]] bool operator==(const McpProtocolGetPromptRequestParams::Meta &other) const;

        /*!
         */
        [[nodiscard]] static McpProtocolGetPromptRequestParams::Meta fromJson(const QJsonObject &obj);
        /*!
         */
        [[nodiscard]] static QJsonObject toJson(const McpProtocolGetPromptRequestParams::Meta &image);
    };

    /*!
     */
    McpProtocolGetPromptRequestParams();
    /*!
     */
    ~McpProtocolGetPromptRequestParams();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolGetPromptRequestParams &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolGetPromptRequestParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolGetPromptRequestParams &image);

    /*!
     */
    [[nodiscard]] std::optional<QMap<QString, QJsonValue>> arguments() const;
    /*!
     */
    void setArguments(std::optional<QMap<QString, QJsonValue>> newArguments);

    /*!
     */
    [[nodiscard]] QString name() const;
    /*!
     */
    void setName(const QString &newName);

    /*!
     */
    [[nodiscard]] std::optional<Meta> meta() const;
    /*!
     */
    void setMeta(std::optional<Meta> newMeta);

private:
    std::optional<Meta> mMeta;
    std::optional<QMap<QString, QJsonValue>> mArguments;
    QString mName;
};
}
Q_DECLARE_TYPEINFO(McpProtocol::McpProtocolGetPromptRequestParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QDebug operator<<(QDebug d, const McpProtocol::McpProtocolGetPromptRequestParams &t);
