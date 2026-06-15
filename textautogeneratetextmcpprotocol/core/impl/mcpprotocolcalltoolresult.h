/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QJsonObject>
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolMeta>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>

class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolCallToolResult
{
public:
    /*!
     */
    McpProtocolCallToolResult();
    /*!
     */
    ~McpProtocolCallToolResult();

    /*!
     */
    // TODO [[nodiscard]] bool operator==(const McpProtocolCallToolResult &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolCallToolResult fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolCallToolResult &image);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);
#if 0
    /*!
     */
    [[nodiscard]] QList<McpProtocolUtils::ContentBlock> content() const;
    /*!
     */
    void setContent(const QList<McpProtocolUtils::ContentBlock> &newContent);
#endif
    /*!
     */
    [[nodiscard]] std::optional<bool> isError() const;
    /*!
     */
    void setIsError(std::optional<bool> newIsError);
    /*!
     */
    [[nodiscard]] std::optional<QMap<QString, QJsonValue>> structuredContent() const;
    /*!
     */
    void setStructuredContent(std::optional<QMap<QString, QJsonValue>> newStructuredContent);

private:
    std::optional<McpProtocolMeta> mMeta;
    // QList<McpProtocolUtils::ContentBlock> mContent;
    std::optional<bool> mIsError;
    std::optional<QMap<QString, QJsonValue>> mStructuredContent;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolCallToolResult, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCallToolResult &t);
