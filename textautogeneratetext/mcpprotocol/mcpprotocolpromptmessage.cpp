/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolpromptmessage.h"
#include <QDebug>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolPromptMessage::McpProtocolPromptMessage() = default;

McpProtocolPromptMessage::~McpProtocolPromptMessage() = default;

bool McpProtocolPromptMessage::operator==(const McpProtocolPromptMessage &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolPromptMessage &t)
{
    return d;
}

McpProtocolPromptMessage McpProtocolPromptMessage::fromJson(const QJsonObject &obj)
{
    McpProtocolPromptMessage modelHint;
    return modelHint;
}

QJsonObject McpProtocolPromptMessage::toJson(const McpProtocolPromptMessage &choice)
{
    QJsonObject obj;
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
