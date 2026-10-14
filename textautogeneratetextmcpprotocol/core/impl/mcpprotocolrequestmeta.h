/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QJsonObject>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
#include <optional>
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
/*!
 * \class TextAutoGenerateTextMcpProtocolCore::McpProtocolRequestMeta
 * \brief The McpProtocolRequestMeta class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateTextMcpProtocolCore
 * \inheaderfile TextAutoGenerateTextMcpProtocolCore/McpProtocolRequestMeta
 *
 * "_meta" field of request params: progress token and other keys.
 */
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolRequestMeta
{
public:
    /*!
     */
    McpProtocolRequestMeta();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolRequestMeta &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolRequestMeta fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolRequestMeta &meta);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolUtils::ProgressToken> progressToken() const;
    /*!
     */
    void setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken);

    /*!
     * Other "_meta" keys (e.g. "io.modelcontextprotocol/related-task")
     */
    [[nodiscard]] QJsonObject additionalProperties() const;
    /*!
     */
    void setAdditionalProperties(const QJsonObject &newAdditionalProperties);

private:
    std::optional<McpProtocolUtils::ProgressToken> mProgressToken;
    QJsonObject mAdditionalProperties;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolRequestMeta, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolRequestMeta &t);
