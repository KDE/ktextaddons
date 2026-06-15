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

McpProtocolCallToolResult::~McpProtocolCallToolResult() = default;

// TODO bool McpProtocolCallToolResult::operator==(const McpProtocolCallToolResult &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCallToolResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "isError:" << t.isError();
    return d;
}

McpProtocolCallToolResult McpProtocolCallToolResult::fromJson(const QJsonObject &obj)
{
    McpProtocolCallToolResult prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    // TODO
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
    // TODO
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
#if 0
QList<McpProtocolUtils::ContentBlock> McpProtocolCallToolResult::content() const
{
    return mContent;
}

void McpProtocolCallToolResult::setContent(const QList<McpProtocolUtils::ContentBlock> &newContent)
{
    mContent = newContent;
}
#endif
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
    mStructuredContent = newStructuredContent;
}
