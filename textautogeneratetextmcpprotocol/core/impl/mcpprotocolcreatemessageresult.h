/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QString>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolAudioContent>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolEmbeddedResource>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolImageContent>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolMeta>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolResourceLink>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTextContent>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolResultContent>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolUseContent>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
class QJsonObject;
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolCreateMessageResult
{
public:
    /*!
     */
    McpProtocolCreateMessageResult();

    /*!
     */
    [[nodiscard]] static McpProtocolCreateMessageResult fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolCreateMessageResult &image);

    /*!
     */
    [[nodiscard]] std::optional<McpProtocolMeta> meta() const;
    /*!
     */
    void setMeta(std::optional<McpProtocolMeta> newMeta);

    /*!
     */
    [[nodiscard]] McpProtocolUtils::CreateMessageResultContent content() const;
    /*!
     */
    void setContent(const McpProtocolUtils::CreateMessageResultContent &newContent);

    /*!
     */
    [[nodiscard]] QString model() const;
    /*!
     */
    void setModel(const QString &newModel);

    /*!
     */
    [[nodiscard]] McpProtocolUtils::Role role() const;
    /*!
     */
    void setRole(McpProtocolUtils::Role newRole);

    /*!
     */
    [[nodiscard]] std::optional<QString> stopReason() const;
    /*!
     */
    void setStopReason(std::optional<QString> newStopReason);

private:
    std::optional<McpProtocolMeta> mMeta;
    McpProtocolUtils::CreateMessageResultContent mContent;
    QString mModel;
    std::optional<QString> mStopReason;
    McpProtocolUtils::Role mRole = McpProtocolUtils::Role::Unknown;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageResult, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageResult &t);
