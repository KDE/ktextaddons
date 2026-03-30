/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocollistpromptsresult.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
#include <utility>
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
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    if (obj.contains("nextCursor"_L1)) {
        prompt.setNextCursor(obj.value("nextCursor"_L1).toString());
    }
    if (obj.contains("prompts"_L1) && obj["prompts"_L1].isArray()) {
        const QJsonArray arr = obj["prompts"_L1].toArray();
        QList<McpProtocolPrompt> lst;
        for (const QJsonValue &v : arr) {
            lst.append(McpProtocolPrompt::fromJson(v.toObject()));
        }
        prompt.setPrompts(lst);
    }
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
    mMeta = std::move(newMeta);
}

std::optional<QString> McpProtocolListPromptsResult::nextCursor() const
{
    return mNextCursor;
}

void McpProtocolListPromptsResult::setNextCursor(std::optional<QString> newNextCursor)
{
    mNextCursor = std::move(newNextCursor);
}

QList<McpProtocolPrompt> McpProtocolListPromptsResult::prompts() const
{
    return mPrompts;
}

void McpProtocolListPromptsResult::setPrompts(const QList<McpProtocolPrompt> &newPrompts)
{
    mPrompts = newPrompts;
}
