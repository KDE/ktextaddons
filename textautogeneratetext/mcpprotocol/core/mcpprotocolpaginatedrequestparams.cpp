/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolpaginatedrequestparams.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolPaginatedRequestParams::McpProtocolPaginatedRequestParams() = default;

McpProtocolPaginatedRequestParams::~McpProtocolPaginatedRequestParams() = default;

bool McpProtocolPaginatedRequestParams::operator==(const McpProtocolPaginatedRequestParams &other) const = default;
bool McpProtocolPaginatedRequestParams::Meta::operator==(const McpProtocolPaginatedRequestParams::Meta &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolPaginatedRequestParams::Meta &t)
{
    d.space() << "progressToken:" << t.progressToken();
    return d;
}

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolPaginatedRequestParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "cursor:" << t.cursor();
    return d;
}

McpProtocolPaginatedRequestParams::Meta McpProtocolPaginatedRequestParams::Meta::fromJson(const QJsonObject &obj)
{
    McpProtocolPaginatedRequestParams::Meta meta;
    if (obj.contains("progressToken"_L1)) {
        meta.setProgressToken(McpProtocolUtils::progressTokenFromJson(obj["progressToken"_L1].toObject()));
    }
    return meta;
}

QJsonObject McpProtocolPaginatedRequestParams::Meta::toJson(const McpProtocolPaginatedRequestParams::Meta &image)
{
    QJsonObject obj;
    if (image.progressToken().has_value()) {
        obj.insert("progressToken"_L1, McpProtocolUtils::progressTokenToJson(*image.progressToken()));
    }
    return obj;
}

McpProtocolPaginatedRequestParams McpProtocolPaginatedRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolPaginatedRequestParams prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolPaginatedRequestParams::Meta::fromJson(obj["_meta"_L1].toObject()));
    }
    prompt.setCursor(obj.value("cursor"_L1).toString());
    return prompt;
}

QJsonObject McpProtocolPaginatedRequestParams::toJson(const McpProtocolPaginatedRequestParams &boolean)
{
    QJsonObject obj;
    obj["cursor"_L1] = boolean.cursor();
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolPaginatedRequestParams::Meta::toJson(*boolean.meta());
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

QString McpProtocolPaginatedRequestParams::cursor() const
{
    return mCursor;
}

void McpProtocolPaginatedRequestParams::setCursor(const QString &newCursor)
{
    mCursor = newCursor;
}

std::optional<McpProtocolUtils::ProgressToken> McpProtocolPaginatedRequestParams::Meta::progressToken() const
{
    return mProgressToken;
}

void McpProtocolPaginatedRequestParams::Meta::setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken)
{
    mProgressToken = std::move(newProgressToken);
}
