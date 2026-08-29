/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcalltoolresult.h"
#include <QDebug>
#include <QJsonArray>

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
    McpProtocolCallToolResult prompt;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    if (obj.contains("isError"_L1)) {
        prompt.setIsError(obj["isError"_L1].toBool());
    }
    if (const QJsonValue structuredContentValue = obj.value("structuredContent"_L1); structuredContentValue.isObject()) {
        const QJsonObject mapObj_structuredContent = structuredContentValue.toObject();
        QMap<QString, QJsonValue> map_structuredContent;
        for (auto it = mapObj_structuredContent.constBegin(); it != mapObj_structuredContent.constEnd(); ++it) {
            map_structuredContent.insert(it.key(), it.value());
        }
        prompt.setStructuredContent(map_structuredContent);
    }
    if (const QJsonValue contentValue = obj.value("content"_L1); contentValue.isArray()) {
        const QJsonArray arr = contentValue.toArray();
        QList<McpProtocolUtils::ContentBlock> content;
        content.reserve(arr.count());
        for (const QJsonValue &v : arr) {
            content.append(McpProtocolUtils::contentBlockFromJson(v));
        }
        prompt.setContent(content);
    }
    return prompt;
}

QJsonObject McpProtocolCallToolResult::toJson(const McpProtocolCallToolResult &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    if (boolean.isError().has_value()) {
        obj["isError"_L1] = *boolean.isError();
    }
    if (boolean.structuredContent().has_value()) {
        QJsonObject map_structuredContent;
        for (auto it = boolean.structuredContent()->constBegin(); it != boolean.structuredContent()->constEnd(); ++it) {
            map_structuredContent.insert(it.key(), it.value());
        }
        obj["structuredContent"_L1] = map_structuredContent;
    }
    QJsonArray arr_content;
    for (const auto &v : boolean.content()) {
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

void McpProtocolCallToolResult::setContent(const QList<McpProtocolUtils::ContentBlock> &newContent)
{
    mContent = newContent;
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
