/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolAudioContent>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolEmbeddedResource>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolImageContent>
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
    McpProtocolSamplingMessage();
    ~McpProtocolSamplingMessage();

private:
    std::optional<McpProtocolMeta> mMeta;
    McpProtocolUtils::CreateMessageResultContent mContent;
    McpProtocolUtils::Role mRole;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateTextMcpProtocolCore::McpProtocolSamplingMessage, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSamplingMessage &t);
