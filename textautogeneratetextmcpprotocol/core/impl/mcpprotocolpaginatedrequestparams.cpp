/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolpaginatedrequestparams.h"
#include <QDebug>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolPaginatedRequestParams::McpProtocolPaginatedRequestParams() = default;

bool McpProtocolPaginatedRequestParams::operator==(const McpProtocolPaginatedRequestParams &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolPaginatedRequestParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "cursor:" << t.cursor();
    return d;
}

McpProtocolPaginatedRequestParams McpProtocolPaginatedRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolPaginatedRequestParams prompt;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        prompt.setMeta(McpProtocolPaginatedRequestParams::Meta::fromJson(metaValue.toObject()));
    }
    if (const QJsonValue cursorValue = obj.value("cursor"_L1); cursorValue.isString()) {
        prompt.setCursor(cursorValue.toString());
    }
    return prompt;
}

QJsonObject McpProtocolPaginatedRequestParams::toJson(const McpProtocolPaginatedRequestParams &paginatedRequestParams)
{
    QJsonObject obj;
    // Empty string is a valid opaque cursor
    if (paginatedRequestParams.cursor().has_value()) {
        obj["cursor"_L1] = *paginatedRequestParams.cursor();
    }
    if (paginatedRequestParams.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolPaginatedRequestParams::Meta::toJson(*paginatedRequestParams.meta());
    }
    return obj;
}

std::optional<McpProtocolPaginatedRequestParams::Meta> McpProtocolPaginatedRequestParams::meta() const
{
    return mMeta;
}

void McpProtocolPaginatedRequestParams::setMeta(std::optional<Meta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<QString> McpProtocolPaginatedRequestParams::cursor() const
{
    return mCursor;
}

void McpProtocolPaginatedRequestParams::setCursor(const std::optional<QString> &newCursor)
{
    mCursor = newCursor;
}
