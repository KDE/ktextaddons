/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolpromptmessage.h"
#include <QDebug>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolPromptMessage::McpProtocolPromptMessage() = default;

McpProtocolPromptMessage::~McpProtocolPromptMessage() = default;

bool McpProtocolPromptMessage::operator==(const McpProtocolPromptMessage &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolPromptMessage &t)
{
    d.space() << "role:" << t.role();
    d.space() << "content:" << McpProtocolUtils::contentBlocktoJson(t.content());
    return d;
}

McpProtocolPromptMessage McpProtocolPromptMessage::fromJson(const QJsonObject &obj)
{
    McpProtocolPromptMessage message;
    if (obj.contains("content"_L1)) {
        message.setContent(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::contentBlockFromJson(obj["content"_L1]));
    }
    if (const QJsonValue roleValue = obj.value("role"_L1); roleValue.isString()) {
        message.setRole(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertRoleFromString(roleValue.toString()));
    }

    return message;
}

QJsonObject McpProtocolPromptMessage::toJson(const McpProtocolPromptMessage &choice)
{
    QJsonObject obj;
    obj["content"_L1] = TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::contentBlocktoJson(choice.content());
    obj["role"_L1] = convertRoleToString(choice.role());
    return obj;
}

McpProtocolUtils::ContentBlock McpProtocolPromptMessage::content() const
{
    return mContent;
}

void McpProtocolPromptMessage::setContent(const McpProtocolUtils::ContentBlock &newContent)
{
    mContent = newContent;
}

McpProtocolUtils::Role McpProtocolPromptMessage::role() const
{
    return mRole;
}

void McpProtocolPromptMessage::setRole(McpProtocolUtils::Role newRole)
{
    mRole = newRole;
}

#include "moc_mcpprotocolpromptmessage.cpp"
