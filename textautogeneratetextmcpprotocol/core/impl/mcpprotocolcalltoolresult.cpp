/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcalltoolresult.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolCallToolResult::McpProtocolCallToolResult() = default;

bool McpProtocolCallToolResult::operator==(const McpProtocolCallToolResult &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCallToolResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "isError:" << t.isError();
    d.space() << "structuredContent:" << t.structuredContent();
    QJsonArray arr_content;
    for (const auto &v : t.content()) {
        arr_content.append(McpProtocolUtils::contentBlocktoJson(v));
    }
    d.space() << "content:" << arr_content;
    return d;
}

McpProtocolCallToolResult McpProtocolCallToolResult::fromJson(const QJsonObject &obj)
{
    McpProtocolCallToolResult result;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        result.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    if (obj.contains("isError"_L1)) {
        result.setIsError(obj["isError"_L1].toBool());
    }
    if (const QJsonValue structuredContentValue = obj.value("structuredContent"_L1); structuredContentValue.isObject()) {
        const QJsonObject mapObj_structuredContent = structuredContentValue.toObject();
        QMap<QString, QJsonValue> map_structuredContent;
        for (auto it = mapObj_structuredContent.constBegin(); it != mapObj_structuredContent.constEnd(); ++it) {
            map_structuredContent.insert(it.key(), it.value());
        }
        result.setStructuredContent(std::move(map_structuredContent));
    }
    if (const QJsonValue contentValue = obj.value("content"_L1); contentValue.isArray()) {
        const QJsonArray arr = contentValue.toArray();
        QList<McpProtocolUtils::ContentBlock> content;
        content.reserve(arr.count());
        for (const QJsonValue &v : arr) {
            // Ignore unknown content
            if (auto block = McpProtocolUtils::contentBlockFromJson(v)) {
                content.append(std::move(*block));
            }
        }
        result.setContent(std::move(content));
    }
    return result;
}

QJsonObject McpProtocolCallToolResult::toJson(const McpProtocolCallToolResult &result)
{
    QJsonObject obj;
    if (result.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*result.meta());
    }
    if (result.isError().has_value()) {
        obj["isError"_L1] = *result.isError();
    }
    if (result.structuredContent().has_value()) {
        QJsonObject map_structuredContent;
        const auto structuredContentValues = *result.structuredContent();
        for (auto it = structuredContentValues.constBegin(); it != structuredContentValues.constEnd(); ++it) {
            map_structuredContent.insert(it.key(), it.value());
        }
        obj["structuredContent"_L1] = map_structuredContent;
    }
    QJsonArray arr_content;
    for (const auto &v : result.content()) {
        arr_content.append(McpProtocolUtils::contentBlocktoJson(v));
    }
    obj["content"_L1] = arr_content;
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolCallToolResult::meta() const
{
    return mMeta;
}

void McpProtocolCallToolResult::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

QList<McpProtocolUtils::ContentBlock> McpProtocolCallToolResult::content() const
{
    return mContent;
}

void McpProtocolCallToolResult::setContent(QList<McpProtocolUtils::ContentBlock> newContent)
{
    mContent = std::move(newContent);
}

std::optional<bool> McpProtocolCallToolResult::isError() const
{
    return mIsError;
}

void McpProtocolCallToolResult::setIsError(std::optional<bool> newIsError)
{
    mIsError = newIsError;
}

std::optional<QMap<QString, QJsonValue>> McpProtocolCallToolResult::structuredContent() const
{
    return mStructuredContent;
}

void McpProtocolCallToolResult::setStructuredContent(std::optional<QMap<QString, QJsonValue>> newStructuredContent)
{
    mStructuredContent = std::move(newStructuredContent);
}
