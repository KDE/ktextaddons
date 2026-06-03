/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QByteArray>
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolMeta>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPrompt>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolListToolsResult
{
public:
    /*!
     */
    McpProtocolListToolsResult();
    /*!
     */
    ~McpProtocolListToolsResult();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolListToolsResult &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolListToolsResult fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolListToolsResult &image);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

    /*!
     */
    [[nodiscard]] std::optional<QString> nextCursor() const;
    /*!
     */
    void setNextCursor(std::optional<QString> newNextCursor);

    /*!
     */
    [[nodiscard]] QList<McpProtocolPrompt> prompts() const;
    /*!
     */
    void setPrompts(const QList<McpProtocolPrompt> &newPrompts);

private:
    std::optional<McpProtocolMeta> mMeta;
    std::optional<QString> mNextCursor;
    // TODO Add missing Tool !!!!
    QList<McpProtocolPrompt> mPrompts;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolListToolsResult, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolListToolsResult &t);
