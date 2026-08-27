/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolAudioContent>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolEmbeddedResource>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolImageContent>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolMeta>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolResourceLink>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTextContent>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolResultContent>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolUseContent>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
class QDebug;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolSamplingMessage
{
public:
    /*!
     */
    McpProtocolSamplingMessage();

    /*!
     */
    [[nodiscard]] bool operator==(const McpProtocolSamplingMessage &other) const;

    /*!
     */
    [[nodiscard]] static McpProtocolSamplingMessage fromJson(const QJsonObject &obj);
    /*!
     */
    [[nodiscard]] static QJsonObject toJson(const McpProtocolSamplingMessage &image);

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
    [[nodiscard]] McpProtocolUtils::Role role() const;
    /*!
     */
    void setRole(McpProtocolUtils::Role newRole);

private:
    std::optional<McpProtocolMeta> mMeta;
    McpProtocolUtils::CreateMessageResultContent mContent;
    McpProtocolUtils::Role mRole = McpProtocolUtils::Role::Unknown;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolSamplingMessage, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSamplingMessage &t);
