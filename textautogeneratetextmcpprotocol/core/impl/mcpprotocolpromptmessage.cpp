/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolpromptmessage.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolPromptMessage::McpProtocolPromptMessage() = default;

McpProtocolPromptMessage::~McpProtocolPromptMessage() = default;

bool McpProtocolPromptMessage::operator==(const McpProtocolPromptMessage &other) const = default;

bool McpProtocolPromptMessage::isValid() const
{
    return mRole != McpProtocolUtils::Role::Unknown;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolPromptMessage &t)
{
    d.space() << "role:" << t.role();
    d.space() << "content:" << McpProtocolUtils::contentBlocktoJson(t.content());
    return d;
}

McpProtocolPromptMessage McpProtocolPromptMessage::fromJson(const QJsonObject &obj)
{
    McpProtocolPromptMessage message;
    if (auto content = TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::contentBlockFromJson(obj.value("content"_L1))) {
        message.setContent(std::move(*content));
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolPromptMessage: missing required field 'content'";
        return {};
    }
    const McpProtocolUtils::Role role = TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertRoleFromString(obj.value("role"_L1).toString());
    if (role == McpProtocolUtils::Role::Unknown) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolPromptMessage: missing required field 'role'";
        return {};
    }
    message.setRole(role);

    return message;
}

QJsonObject McpProtocolPromptMessage::toJson(const McpProtocolPromptMessage &message)
{
    QJsonObject obj;
    obj["content"_L1] = TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::contentBlocktoJson(message.content());
    // Unknown value is not valid, don't write it
    if (message.role() != McpProtocolUtils::Role::Unknown) {
        obj["role"_L1] = convertRoleToString(message.role());
    }
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
