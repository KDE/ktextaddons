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
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolSetLevelRequestParams
{
public:
    struct Meta {
        std::optional<McpProtocolUtils::ProgressToken> mProgressToken;

        [[nodiscard]] std::optional<McpProtocolUtils::ProgressToken> progressToken() const;
        void setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken);
        [[nodiscard]] bool operator==(const McpProtocolSetLevelRequestParams::Meta &other) const;

        /*!
         */
        [[nodiscard]] static McpProtocolSetLevelRequestParams::Meta fromJson(const QJsonObject &obj);
        /*!
         */
        [[nodiscard]] static QJsonObject toJson(const McpProtocolSetLevelRequestParams::Meta &image);
    };

    /*!
     */
    McpProtocolSetLevelRequestParams();
    /*!
     */
    ~McpProtocolSetLevelRequestParams();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolSetLevelRequestParams &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolSetLevelRequestParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolSetLevelRequestParams &image);

    /*!
     */
    [[nodiscard]] std::optional<Meta> meta() const;
    /*!
     */
    void setMeta(std::optional<Meta> newMeta);

    McpProtocolUtils::LoggingLevel level() const;
    void setLevel(McpProtocolUtils::LoggingLevel newLevel);

private:
    std::optional<Meta> mMeta;
    McpProtocolUtils::LoggingLevel mLevel = McpProtocolUtils::LoggingLevel::Unknown;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolSetLevelRequestParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSetLevelRequestParams &t);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSetLevelRequestParams::Meta &t);
