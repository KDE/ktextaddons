/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QJsonObject>
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
#include <optional>
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolSubscribeRequestParams
{
public:
    struct TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT Meta {
        std::optional<McpProtocolUtils::ProgressToken> mProgressToken;
        // Other _meta keys (e.g. "io.modelcontextprotocol/related-task")
        QJsonObject mAdditionalProperties;

        [[nodiscard]] std::optional<McpProtocolUtils::ProgressToken> progressToken() const;
        void setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken);
        [[nodiscard]] QJsonObject additionalProperties() const;
        void setAdditionalProperties(const QJsonObject &newAdditionalProperties);
        [[nodiscard]] bool operator==(const McpProtocolSubscribeRequestParams::Meta &other) const;

        /*!
         */
        [[nodiscard]] static McpProtocolSubscribeRequestParams::Meta fromJson(const QJsonObject &obj);
        /*!
         */
        [[nodiscard]] static QJsonObject toJson(const McpProtocolSubscribeRequestParams::Meta &meta);
    };

    /*!
     */
    McpProtocolSubscribeRequestParams();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolSubscribeRequestParams &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolSubscribeRequestParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolSubscribeRequestParams &subscribeRequestParams);

    /*!
     */
    [[nodiscard]] std::optional<Meta> meta() const;
    /*!
     */
    void setMeta(std::optional<Meta> newMeta);

    /*!
     * \brief uri
     * \return
     */
    [[nodiscard]] QString uri() const;
    /*!
     * \brief setUri
     * \param newUri
     */
    void setUri(const QString &newUri);

private:
    std::optional<Meta> mMeta;
    QString mUri;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscribeRequestParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscribeRequestParams &t);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscribeRequestParams::Meta &t);
