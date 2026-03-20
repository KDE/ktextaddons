/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolprompt.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolPrompt::McpProtocolPrompt() = default;

McpProtocolPrompt::~McpProtocolPrompt() = default;

bool McpProtocolPrompt::operator==(const McpProtocolPrompt &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolPrompt &t)
{
    return d;
}

McpProtocolPrompt McpProtocolPrompt::fromJson(const QJsonObject &obj)
{
    McpProtocolPrompt prompt;
    return prompt;
}

QJsonObject McpProtocolPrompt::toJson(const McpProtocolPrompt &boolean)
{
    QJsonObject obj;
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolPrompt::meta() const
{
    return mMeta;
}

void McpProtocolPrompt::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<QList<McpProtocolPromptArgument>> McpProtocolPrompt::arguments() const
{
    return mArguments;
}

void McpProtocolPrompt::setArguments(std::optional<QList<McpProtocolPromptArgument>> newArguments)
{
    mArguments = std::move(newArguments);
}

std::optional<QString> McpProtocolPrompt::description() const
{
    return mDescription;
}

void McpProtocolPrompt::setDescription(std::optional<QString> newDescription)
{
    mDescription = std::move(newDescription);
}

std::optional<QList<McpProtocolIcon>> McpProtocolPrompt::icons() const
{
    return mIcons;
}

void McpProtocolPrompt::setIcons(std::optional<QList<McpProtocolIcon>> newIcons)
{
    mIcons = std::move(newIcons);
}

QString McpProtocolPrompt::name() const
{
    return mName;
}

void McpProtocolPrompt::setName(const QString &newName)
{
    mName = newName;
}

std::optional<QString> McpProtocolPrompt::title() const
{
    return mTitle;
}

void McpProtocolPrompt::setTitle(std::optional<QString> newTitle)
{
    mTitle = std::move(newTitle);
}
