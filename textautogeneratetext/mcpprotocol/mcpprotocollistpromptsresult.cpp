/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocollistpromptsresult.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolListPromptsResult::McpProtocolListPromptsResult() = default;

McpProtocolListPromptsResult::~McpProtocolListPromptsResult() = default;

bool McpProtocolListPromptsResult::operator==(const McpProtocolListPromptsResult &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolListPromptsResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "nextCursor:" << t.nextCursor();
    d.space() << "prompts:" << t.prompts();
    return d;
}

McpProtocolListPromptsResult McpProtocolListPromptsResult::fromJson(const QJsonObject &obj)
{
    McpProtocolListPromptsResult prompt;
    // TODO
    return prompt;
}

QJsonObject McpProtocolListPromptsResult::toJson(const McpProtocolListPromptsResult &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    if (boolean.nextCursor().has_value()) {
        obj["nextCursor"_L1] = *boolean.nextCursor();
    }
    QJsonArray promptsArray;
    for (const auto &v : boolean.prompts()) {
        promptsArray.append(McpProtocolPrompt::toJson(v));
    }
    obj["prompts"_L1] = promptsArray;
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolListPromptsResult::meta() const
{
    return mMeta;
}

void McpProtocolListPromptsResult::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = newMeta;
}

std::optional<QString> McpProtocolListPromptsResult::nextCursor() const
{
    return mNextCursor;
}

void McpProtocolListPromptsResult::setNextCursor(std::optional<QString> newNextCursor)
{
    mNextCursor = newNextCursor;
}

QList<McpProtocolPrompt> McpProtocolListPromptsResult::prompts() const
{
    return mPrompts;
}

void McpProtocolListPromptsResult::setPrompts(const QList<McpProtocolPrompt> &newPrompts)
{
    mPrompts = newPrompts;
}
