/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolpaginatedresult.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolPaginatedResult::McpProtocolPaginatedResult() = default;

bool McpProtocolPaginatedResult::operator==(const McpProtocolPaginatedResult &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolPaginatedResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "nextCursor:" << t.nextCursor();
    return d;
}

McpProtocolPaginatedResult McpProtocolPaginatedResult::fromJson(const QJsonObject &obj)
{
    McpProtocolPaginatedResult prompt;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    if (obj.contains("nextCursor"_L1)) {
        prompt.setNextCursor(obj.value("nextCursor"_L1).toString());
    }
    return prompt;
}

QJsonObject McpProtocolPaginatedResult::toJson(const McpProtocolPaginatedResult &paginatedResult)
{
    QJsonObject obj;
    if (paginatedResult.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*paginatedResult.meta());
    }
    if (paginatedResult.nextCursor().has_value()) {
        obj["nextCursor"_L1] = *paginatedResult.nextCursor();
    }
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolPaginatedResult::meta() const
{
    return mMeta;
}

void McpProtocolPaginatedResult::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<QString> McpProtocolPaginatedResult::nextCursor() const
{
    return mNextCursor;
}

void McpProtocolPaginatedResult::setNextCursor(std::optional<QString> newNextCursor)
{
    mNextCursor = std::move(newNextCursor);
}
