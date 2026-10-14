/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocollisttoolsresult.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolListToolsResult::McpProtocolListToolsResult() = default;

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
    McpProtocolListToolsResult result;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        result.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    if (const QJsonValue nextCursorValue = obj.value("nextCursor"_L1); nextCursorValue.isString()) {
        result.setNextCursor(nextCursorValue.toString());
    }
    if (const QJsonValue toolsValue = obj.value("tools"_L1); toolsValue.isArray()) {
        const QJsonArray arr = toolsValue.toArray();
        QList<McpProtocolTool> lst;
        lst.reserve(arr.count());
        for (const auto &v : arr) {
            if (const McpProtocolTool item = McpProtocolTool::fromJson(v.toObject()); item.isValid()) {
                lst.append(item);
            }
        }
        result.setTools(std::move(lst));
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolListToolsResult: missing required field 'tools'";
        return {};
    }
    return result;
}

QJsonObject McpProtocolListToolsResult::toJson(const McpProtocolListToolsResult &result)
{
    QJsonObject obj;
    if (result.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*result.meta());
    }
    if (result.nextCursor().has_value()) {
        obj["nextCursor"_L1] = *result.nextCursor();
    }
    QJsonArray promptsArray;
    const auto tools = result.tools();
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

void McpProtocolListToolsResult::setTools(QList<McpProtocolTool> newTools)
{
    mTools = std::move(newTools);
}
