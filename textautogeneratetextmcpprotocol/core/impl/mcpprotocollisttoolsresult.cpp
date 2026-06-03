/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocollisttoolsresult.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolListToolsResult::McpProtocolListToolsResult() = default;

McpProtocolListToolsResult::~McpProtocolListToolsResult() = default;

bool McpProtocolListToolsResult::operator==(const McpProtocolListToolsResult &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolListToolsResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "nextCursor:" << t.nextCursor();
    d.space() << "tools:" << t.tools();
    return d;
}

McpProtocolListToolsResult McpProtocolListToolsResult::fromJson(const QJsonObject &obj)
{
    McpProtocolListToolsResult prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    if (obj.contains("nextCursor"_L1)) {
        prompt.setNextCursor(obj.value("nextCursor"_L1).toString());
    }
    if (obj.contains("tools"_L1) && obj["tools"_L1].isArray()) {
        const QJsonArray arr = obj["tools"_L1].toArray();
        QList<McpProtocolTool> lst;
        for (const auto &v : arr) {
            lst.append(McpProtocolTool::fromJson(v.toObject()));
        }
        prompt.setTools(lst);
    }
    return prompt;
}

QJsonObject McpProtocolListToolsResult::toJson(const McpProtocolListToolsResult &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    if (boolean.nextCursor().has_value()) {
        obj["nextCursor"_L1] = *boolean.nextCursor();
    }
    QJsonArray promptsArray;
    const auto tools = boolean.tools();
    for (const auto &v : tools) {
        promptsArray.append(McpProtocolTool::toJson(v));
    }
    obj["tools"_L1] = promptsArray;
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolListToolsResult::meta() const
{
    return mMeta;
}

void McpProtocolListToolsResult::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<QString> McpProtocolListToolsResult::nextCursor() const
{
    return mNextCursor;
}

void McpProtocolListToolsResult::setNextCursor(std::optional<QString> newNextCursor)
{
    mNextCursor = std::move(newNextCursor);
}

QList<McpProtocolTool> McpProtocolListToolsResult::tools() const
{
    return mTools;
}

void McpProtocolListToolsResult::setTools(const QList<McpProtocolTool> &newTools)
{
    mTools = newTools;
}
