/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocollistresourcesresult.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
#include <utility>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolListResourcesResult::McpProtocolListResourcesResult() = default;

McpProtocolListResourcesResult::~McpProtocolListResourcesResult() = default;

bool McpProtocolListResourcesResult::operator==(const McpProtocolListResourcesResult &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolListResourcesResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "nextCursor:" << t.nextCursor();
    return d;
}

McpProtocolListResourcesResult McpProtocolListResourcesResult::fromJson(const QJsonObject &obj)
{
    McpProtocolListResourcesResult prompt;
    // TODO
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
    // TODO
    /*
    QJsonArray arr_resources;
    for (const auto &v : data._resources) arr_resources.append(toJson(v));
    obj.insert("resources"_L1, arr_resources);
    */
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
