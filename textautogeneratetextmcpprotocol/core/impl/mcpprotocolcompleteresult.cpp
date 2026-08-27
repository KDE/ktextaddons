/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcompleteresult.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonArray>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolCompleteResult::McpProtocolCompleteResult() = default;

bool McpProtocolCompleteResult::operator==(const McpProtocolCompleteResult &other) const = default;

bool McpProtocolCompleteResult::Completion::operator==(const McpProtocolCompleteResult::Completion &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCompleteResult::Completion &t)
{
    d.space() << "values:" << t.values();
    d.space() << "hasMore:" << t.hasMore();
    d.space() << "total:" << t.total();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCompleteResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "completion:" << t.completion();
    return d;
}

McpProtocolCompleteResult::Completion McpProtocolCompleteResult::Completion::fromJson(const QJsonObject &obj)
{
    if (!obj.contains("values"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: values";
        return {};
    }
    McpProtocolCompleteResult::Completion completion;
    if (obj["values"_L1].isArray()) {
        const QJsonArray arr = obj["values"_L1].toArray();
        QStringList values;
        values.reserve(arr.count());
        for (const QJsonValue &v : arr) {
            values.append(v.toString());
        }
        completion.setValues(values);
    }
    if (obj.contains("hasMore"_L1)) {
        completion.setHasMore(obj.value("hasMore"_L1).toBool());
    }
    if (obj.contains("total"_L1)) {
        completion.setTotal(obj.value("total"_L1).toInt());
    }
    return completion;
}

QJsonObject McpProtocolCompleteResult::Completion::toJson(const McpProtocolCompleteResult::Completion &completion)
{
    QJsonObject obj;
    QJsonArray arr_values;
    for (const auto &v : completion.values()) {
        arr_values.append(v);
    }
    obj["values"_L1] = arr_values;
    if (completion.hasMore().has_value()) {
        obj.insert("hasMore"_L1, *completion.hasMore());
    }
    if (completion.total().has_value()) {
        obj.insert("total"_L1, *completion.total());
    }
    return obj;
}

QStringList McpProtocolCompleteResult::Completion::values() const
{
    return mValues;
}

void McpProtocolCompleteResult::Completion::setValues(const QStringList &newValues)
{
    mValues = newValues;
}

std::optional<bool> McpProtocolCompleteResult::Completion::hasMore() const
{
    return mHasMore;
}

void McpProtocolCompleteResult::Completion::setHasMore(std::optional<bool> newHasMore)
{
    mHasMore = newHasMore;
}

std::optional<int> McpProtocolCompleteResult::Completion::total() const
{
    return mTotal;
}

void McpProtocolCompleteResult::Completion::setTotal(std::optional<int> newTotal)
{
    mTotal = newTotal;
}

McpProtocolCompleteResult McpProtocolCompleteResult::fromJson(const QJsonObject &obj)
{
    McpProtocolCompleteResult prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    if (!obj.contains("completion"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: completion";
        return prompt;
    }
    if (obj["completion"_L1].isObject()) {
        prompt.setCompletion(McpProtocolCompleteResult::Completion::fromJson(obj["completion"_L1].toObject()));
    }
    return prompt;
}

QJsonObject McpProtocolCompleteResult::toJson(const McpProtocolCompleteResult &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    obj["completion"_L1] = McpProtocolCompleteResult::Completion::toJson(boolean.completion());
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolCompleteResult::meta() const
{
    return mMeta;
}

void McpProtocolCompleteResult::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

McpProtocolCompleteResult::Completion McpProtocolCompleteResult::completion() const
{
    return mCompletion;
}

void McpProtocolCompleteResult::setCompletion(const Completion &newCompletion)
{
    mCompletion = newCompletion;
}
