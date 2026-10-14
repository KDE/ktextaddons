/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocollistresourcetemplatesresult.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <utility>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolListResourceTemplatesResult::McpProtocolListResourceTemplatesResult() = default;

bool McpProtocolListResourceTemplatesResult::operator==(const McpProtocolListResourceTemplatesResult &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolListResourceTemplatesResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "nextCursor:" << t.nextCursor();
    d.space() << "resourceTemplates:" << t.resourceTemplates();
    return d;
}

McpProtocolListResourceTemplatesResult McpProtocolListResourceTemplatesResult::fromJson(const QJsonObject &obj)
{
    McpProtocolListResourceTemplatesResult result;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        result.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    if (const QJsonValue nextCursorValue = obj.value("nextCursor"_L1); nextCursorValue.isString()) {
        result.setNextCursor(nextCursorValue.toString());
    }
    if (const QJsonValue resourceTemplatesValue = obj.value("resourceTemplates"_L1); resourceTemplatesValue.isArray()) {
        const QJsonArray arr = resourceTemplatesValue.toArray();
        QList<McpProtocolResourceTemplate> lst;
        lst.reserve(arr.count());
        for (const auto &v : arr) {
            if (const McpProtocolResourceTemplate item = McpProtocolResourceTemplate::fromJson(v.toObject()); item.isValid()) {
                lst.append(item);
            }
        }
        result.setResourceTemplates(std::move(lst));
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolListResourceTemplatesResult: missing required field 'resourceTemplates'";
        return {};
    }

    return result;
}

QJsonObject McpProtocolListResourceTemplatesResult::toJson(const McpProtocolListResourceTemplatesResult &result)
{
    QJsonObject obj;
    if (result.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*result.meta());
    }
    if (result.nextCursor().has_value()) {
        obj["nextCursor"_L1] = *result.nextCursor();
    }
    QJsonArray arr_resourceTemplates;
    for (const auto &v : result.resourceTemplates()) {
        arr_resourceTemplates.append(McpProtocolResourceTemplate::toJson(v));
    }
    obj["resourceTemplates"_L1] = arr_resourceTemplates;

    return obj;
}

std::optional<McpProtocolMeta> McpProtocolListResourceTemplatesResult::meta() const
{
    return mMeta;
}

void McpProtocolListResourceTemplatesResult::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<QString> McpProtocolListResourceTemplatesResult::nextCursor() const
{
    return mNextCursor;
}

void McpProtocolListResourceTemplatesResult::setNextCursor(std::optional<QString> newNextCursor)
{
    mNextCursor = std::move(newNextCursor);
}

QList<McpProtocolResourceTemplate> McpProtocolListResourceTemplatesResult::resourceTemplates() const
{
    return mResourceTemplates;
}

void McpProtocolListResourceTemplatesResult::setResourceTemplates(QList<McpProtocolResourceTemplate> newResourceTemplates)
{
    mResourceTemplates = std::move(newResourceTemplates);
}
