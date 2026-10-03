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
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolRequestParams
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
        [[nodiscard]] bool operator==(const McpProtocolRequestParams::Meta &other) const;

        /*!
         */
        [[nodiscard]] static McpProtocolRequestParams::Meta fromJson(const QJsonObject &obj);
        /*!
         */
        [[nodiscard]] static QJsonObject toJson(const McpProtocolRequestParams::Meta &meta);
    };

    /*!
     */
    McpProtocolRequestParams();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolRequestParams &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolRequestParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolRequestParams &requestParams);

    /*!
     */
    [[nodiscard]] std::optional<Meta> meta() const;
    /*!
     */
    void setMeta(std::optional<Meta> newMeta);

private:
    std::optional<Meta> mMeta;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolRequestParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolRequestParams &t);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolRequestParams::Meta &t);
