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
bool McpProtocolPaginatedRequestParams::Meta::operator==(const McpProtocolPaginatedRequestParams::Meta &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolPaginatedRequestParams::Meta &t)
{
    d.space() << "progressToken:" << t.progressToken();
    d.space() << "additionalProperties:" << t.additionalProperties();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolPaginatedRequestParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "cursor:" << t.cursor();
    return d;
}

McpProtocolPaginatedRequestParams::Meta McpProtocolPaginatedRequestParams::Meta::fromJson(const QJsonObject &obj)
{
    McpProtocolPaginatedRequestParams::Meta meta;
    if (obj.contains("progressToken"_L1)) {
        meta.setProgressToken(McpProtocolUtils::progressTokenFromJson(obj["progressToken"_L1]));
    }
    QJsonObject additionalProperties = obj;
    additionalProperties.remove("progressToken"_L1);
    meta.setAdditionalProperties(additionalProperties);
    return meta;
}

QJsonObject McpProtocolPaginatedRequestParams::Meta::toJson(const McpProtocolPaginatedRequestParams::Meta &meta)
{
    QJsonObject obj = meta.additionalProperties();
    if (meta.progressToken().has_value()) {
        obj.insert("progressToken"_L1, McpProtocolUtils::progressTokenToJson(*meta.progressToken()));
    }
    return obj;
}

McpProtocolPaginatedRequestParams McpProtocolPaginatedRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolPaginatedRequestParams prompt;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        prompt.setMeta(McpProtocolPaginatedRequestParams::Meta::fromJson(metaValue.toObject()));
    }
    prompt.setCursor(obj.value("cursor"_L1).toString());
    return prompt;
}

QJsonObject McpProtocolPaginatedRequestParams::toJson(const McpProtocolPaginatedRequestParams &paginatedRequestParams)
{
    QJsonObject obj;
    if (!paginatedRequestParams.cursor().isEmpty()) {
        obj["cursor"_L1] = paginatedRequestParams.cursor();
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

QJsonObject McpProtocolPaginatedRequestParams::Meta::additionalProperties() const
{
    return mAdditionalProperties;
}

void McpProtocolPaginatedRequestParams::Meta::setAdditionalProperties(const QJsonObject &newAdditionalProperties)
{
    mAdditionalProperties = newAdditionalProperties;
}
