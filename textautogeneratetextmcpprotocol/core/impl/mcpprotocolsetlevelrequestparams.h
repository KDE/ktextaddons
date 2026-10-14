/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QJsonObject>
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolRequestMeta>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
#include <optional>
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolSetLevelRequestParams
{
public:
    using Meta = McpProtocolRequestMeta;

    /*!
     */
    McpProtocolSetLevelRequestParams();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolSetLevelRequestParams &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolSetLevelRequestParams fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolSetLevelRequestParams &setLevelRequestParams);

    /*!
     */
    [[nodiscard]] bool isValid() const;

    /*!
     */
    [[nodiscard]] std::optional<Meta> meta() const;
    /*!
     */
    void setMeta(std::optional<Meta> newMeta);

    [[nodiscard]] McpProtocolUtils::LoggingLevel level() const;
    void setLevel(McpProtocolUtils::LoggingLevel newLevel);

private:
    std::optional<Meta> mMeta;
    McpProtocolUtils::LoggingLevel mLevel = McpProtocolUtils::LoggingLevel::Unknown;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolSetLevelRequestParams, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSetLevelRequestParams &t);
