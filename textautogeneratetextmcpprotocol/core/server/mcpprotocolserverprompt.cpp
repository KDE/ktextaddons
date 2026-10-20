/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolserverprompt.h"
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPromptArgument>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPromptMessage>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTextContent>
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolServerPrompt::McpProtocolServerPrompt() = default;

McpProtocolServerPrompt::~McpProtocolServerPrompt() = default;

McpProtocolPrompt McpProtocolServerPrompt::createPrompt(const QString &name, const QString &description, const QList<McpProtocolPromptArgument> &arguments)
{
    McpProtocolPrompt prompt;
    prompt.setName(name);
    if (!description.isEmpty()) {
        prompt.setDescription(description);
    }
    if (!arguments.isEmpty()) {
        prompt.setArguments(arguments);
    }
    return prompt;
}

McpProtocolPromptArgument McpProtocolServerPrompt::createArgument(const QString &name, const QString &description, bool required)
{
    McpProtocolPromptArgument argument;
    argument.setName(name);
    if (!description.isEmpty()) {
        argument.setDescription(description);
    }
    if (required) {
        argument.setRequired(true);
    }
    return argument;
}

McpProtocolGetPromptResult McpProtocolServerPrompt::createUserTextResult(const QString &text, const QString &description)
{
    McpProtocolTextContent content;
    content.setText(text);
    McpProtocolPromptMessage message;
    message.setRole(McpProtocolUtils::Role::User);
    message.setContent(content);
    McpProtocolGetPromptResult result;
    if (!description.isEmpty()) {
        result.setDescription(description);
    }
    result.setMessages({message});
    return result;
}
