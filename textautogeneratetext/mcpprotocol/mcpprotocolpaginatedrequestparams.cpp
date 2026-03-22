/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolpaginatedrequestparams.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolPaginatedRequestParams::McpProtocolPaginatedRequestParams() = default;

McpProtocolPaginatedRequestParams::~McpProtocolPaginatedRequestParams() = default;

bool McpProtocolPaginatedRequestParams::operator==(const McpProtocolPaginatedRequestParams &other) const = default;
bool McpProtocolPaginatedRequestParams::Meta::operator==(const McpProtocolPaginatedRequestParams::Meta &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolPaginatedRequestParams &t)
{
    return d;
}

McpProtocolPaginatedRequestParams::Meta McpProtocolPaginatedRequestParams::Meta::fromJson(const QJsonObject &obj)
{
    return {};
}

QJsonObject McpProtocolPaginatedRequestParams::Meta::toJson(const McpProtocolPaginatedRequestParams::Meta &image)
{
    QJsonObject obj;
#if 0
    if (image.progressToken().has_value()) {
        obj.insert("progressToken", McpProtocolUtils::toJson(*image.progressToken()));
    }
#endif
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
