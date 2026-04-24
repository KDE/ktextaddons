/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocollistresourcetemplatesresult.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QJsonArray>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolListResourceTemplatesResult::McpProtocolListResourceTemplatesResult() = default;

McpProtocolListResourceTemplatesResult::~McpProtocolListResourceTemplatesResult() = default;

bool McpProtocolListResourceTemplatesResult::operator==(const McpProtocolListResourceTemplatesResult &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolListResourceTemplatesResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "nextCursor:" << t.nextCursor();
    d.space() << "resourceTemplates:" << t.resourceTemplates();
    return d;
}

McpProtocolListResourceTemplatesResult McpProtocolListResourceTemplatesResult::fromJson(const QJsonObject &obj)
{
    McpProtocolListResourceTemplatesResult prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    if (obj.contains("nextCursor"_L1)) {
        prompt.setNextCursor(obj.value("nextCursor"_L1).toString());
    }
    if (obj.contains("resourceTemplates"_L1) && obj["resourceTemplates"_L1].isArray()) {
        const QJsonArray arr = obj["resourceTemplates"_L1].toArray();
        QList<McpProtocolResourceTemplate> lst;
        for (const QJsonValue &v : arr) {
            lst.append(McpProtocolResourceTemplate::fromJson(v.toObject()));
        }
        prompt.setResourceTemplates(lst);
    }

    return prompt;
}

QJsonObject McpProtocolListResourceTemplatesResult::toJson(const McpProtocolListResourceTemplatesResult &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    if (boolean.nextCursor().has_value()) {
        obj["nextCursor"_L1] = *boolean.nextCursor();
    }
    QJsonArray arr_resourceTemplates;
    for (const auto &v : boolean.resourceTemplates()) {
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

void McpProtocolListResourceTemplatesResult::setResourceTemplates(const QList<McpProtocolResourceTemplate> &newResourceTemplates)
{
    mResourceTemplates = newResourceTemplates;
}
