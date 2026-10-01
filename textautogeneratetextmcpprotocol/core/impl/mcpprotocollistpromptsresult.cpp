/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocollistpromptsresult.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolListPromptsResult::McpProtocolListPromptsResult() = default;

bool McpProtocolListPromptsResult::operator==(const McpProtocolListPromptsResult &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolListPromptsResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "nextCursor:" << t.nextCursor();
    d.space() << "prompts:" << t.prompts();
    return d;
}

McpProtocolListPromptsResult McpProtocolListPromptsResult::fromJson(const QJsonObject &obj)
{
    McpProtocolListPromptsResult result;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        result.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    if (obj.contains("nextCursor"_L1)) {
        result.setNextCursor(obj.value("nextCursor"_L1).toString());
    }
    if (const QJsonValue promptsValue = obj.value("prompts"_L1); promptsValue.isArray()) {
        const QJsonArray arr = promptsValue.toArray();
        QList<McpProtocolPrompt> lst;
        lst.reserve(arr.count());
        for (const auto &v : arr) {
            lst.append(McpProtocolPrompt::fromJson(v.toObject()));
        }
        result.setPrompts(std::move(lst));
    }
    return result;
}

QJsonObject McpProtocolListPromptsResult::toJson(const McpProtocolListPromptsResult &result)
{
    QJsonObject obj;
    if (result.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*result.meta());
    }
    if (result.nextCursor().has_value()) {
        obj["nextCursor"_L1] = *result.nextCursor();
    }
    QJsonArray promptsArray;
    for (const auto &v : result.prompts()) {
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

void McpProtocolListPromptsResult::setPrompts(QList<McpProtocolPrompt> newPrompts)
{
    mPrompts = std::move(newPrompts);
}
