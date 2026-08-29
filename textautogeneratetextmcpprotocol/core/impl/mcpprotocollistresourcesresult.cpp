/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocollistresourcesresult.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <utility>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolListResourcesResult::McpProtocolListResourcesResult() = default;

bool McpProtocolListResourcesResult::operator==(const McpProtocolListResourcesResult &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolListResourcesResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "nextCursor:" << t.nextCursor();
    d.space() << "resources:" << t.resources();
    return d;
}

McpProtocolListResourcesResult McpProtocolListResourcesResult::fromJson(const QJsonObject &obj)
{
    McpProtocolListResourcesResult prompt;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    if (obj.contains("nextCursor"_L1)) {
        prompt.setNextCursor(obj.value("nextCursor"_L1).toString());
    }
    if (const QJsonValue resourcesValue = obj.value("resources"_L1); resourcesValue.isArray()) {
        const QJsonArray arr = resourcesValue.toArray();
        QList<McpProtocolResource> res;
        res.reserve(arr.count());
        for (const auto &v : arr) {
            res.append(McpProtocolResource::fromJson(v.toObject()));
        }
        prompt.setResources(res);
    }
    return prompt;
}

QJsonObject McpProtocolListResourcesResult::toJson(const McpProtocolListResourcesResult &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    if (boolean.nextCursor().has_value()) {
        obj.insert("nextCursor"_L1, *boolean.nextCursor());
    }
    QJsonArray arr_resources;
    for (const auto &v : boolean.resources()) {
        arr_resources.append(McpProtocolResource::toJson(v));
    }
    obj.insert("resources"_L1, arr_resources);
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolListResourcesResult::meta() const
{
    return mMeta;
}

void McpProtocolListResourcesResult::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<QString> McpProtocolListResourcesResult::nextCursor() const
{
    return mNextCursor;
}

void McpProtocolListResourcesResult::setNextCursor(std::optional<QString> newNextCursor)
{
    mNextCursor = std::move(newNextCursor);
}

QList<McpProtocolResource> McpProtocolListResourcesResult::resources() const
{
    return mResources;
}

void McpProtocolListResourcesResult::setResources(const QList<McpProtocolResource> &newResources)
{
    mResources = newResources;
}
