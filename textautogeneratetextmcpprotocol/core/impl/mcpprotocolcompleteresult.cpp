/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcompleteresult.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <utility>

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
    const QJsonValue valuesValue = obj.value("values"_L1);
    if (!valuesValue.isArray()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolCompleteResult::Completion: missing required field 'values'";
        return {};
    }
    McpProtocolCompleteResult::Completion completion;
    {
        const QJsonArray arr = valuesValue.toArray();
        QStringList values;
        values.reserve(arr.count());
        for (const QJsonValue &v : arr) {
            values.append(v.toString());
        }
        completion.setValues(std::move(values));
    }
    if (obj.contains("hasMore"_L1)) {
        completion.setHasMore(obj.value("hasMore"_L1).toBool());
    }
    if (const QJsonValue totalValue = obj.value("total"_L1); totalValue.isDouble()) {
        completion.setTotal(totalValue.toInt());
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

void McpProtocolCompleteResult::Completion::setValues(QStringList newValues)
{
    mValues = std::move(newValues);
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
    const QJsonValue completionValue = obj.value("completion"_L1);
    if (!completionValue.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolCompleteResult: missing required field 'completion'";
        return {};
    }
    const QJsonObject completionObj = completionValue.toObject();
    // Completion::fromJson() rejects it when "values" is missing; an empty completion is valid, so check it here
    if (!completionObj.value("values"_L1).isArray()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolCompleteResult: invalid field 'completion'";
        return {};
    }
    McpProtocolCompleteResult result;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        result.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    result.setCompletion(McpProtocolCompleteResult::Completion::fromJson(completionObj));
    return result;
}

QJsonObject McpProtocolCompleteResult::toJson(const McpProtocolCompleteResult &result)
{
    QJsonObject obj;
    if (result.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*result.meta());
    }
    obj["completion"_L1] = McpProtocolCompleteResult::Completion::toJson(result.completion());
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

void McpProtocolCompleteResult::setCompletion(Completion newCompletion)
{
    mCompletion = std::move(newCompletion);
}
