/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolrequestparams.h"
#include <QDebug>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolRequestParams::McpProtocolRequestParams() = default;

bool McpProtocolRequestParams::operator==(const McpProtocolRequestParams &other) const = default;
bool McpProtocolRequestParams::Meta::operator==(const McpProtocolRequestParams::Meta &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolRequestParams &t)
{
    d.space() << "meta:" << t.meta();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolRequestParams::Meta &t)
{
    d.space() << "progressToken:" << t.progressToken();
    d.space() << "additionalProperties:" << t.additionalProperties();
    return d;
}

McpProtocolRequestParams::Meta McpProtocolRequestParams::Meta::fromJson(const QJsonObject &obj)
{
    McpProtocolRequestParams::Meta meta;
    if (obj.contains("progressToken"_L1)) {
        meta.setProgressToken(McpProtocolUtils::progressTokenFromJson(obj["progressToken"_L1]));
    }
    QJsonObject additionalProperties = obj;
    additionalProperties.remove("progressToken"_L1);
    meta.setAdditionalProperties(additionalProperties);
    return meta;
}

QJsonObject McpProtocolRequestParams::Meta::toJson(const McpProtocolRequestParams::Meta &meta)
{
    QJsonObject obj = meta.additionalProperties();
    if (meta.progressToken().has_value()) {
        obj["progressToken"_L1] = McpProtocolUtils::progressTokenToJson(*meta.progressToken());
    }
    return obj;
}

McpProtocolRequestParams McpProtocolRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolRequestParams prompt;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        prompt.setMeta(McpProtocolRequestParams::Meta::fromJson(metaValue.toObject()));
    }
    return prompt;
}

QJsonObject McpProtocolRequestParams::toJson(const McpProtocolRequestParams &requestParams)
{
    QJsonObject obj;
    if (requestParams.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolRequestParams::Meta::toJson(*requestParams.meta());
    }
    return obj;
}

std::optional<McpProtocolRequestParams::Meta> McpProtocolRequestParams::meta() const
{
    return mMeta;
}

void McpProtocolRequestParams::setMeta(std::optional<Meta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<McpProtocolUtils::ProgressToken> McpProtocolRequestParams::Meta::progressToken() const
{
    return mProgressToken;
}

void McpProtocolRequestParams::Meta::setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken)
{
    mProgressToken = std::move(newProgressToken);
}

QJsonObject McpProtocolRequestParams::Meta::additionalProperties() const
{
    return mAdditionalProperties;
}

void McpProtocolRequestParams::Meta::setAdditionalProperties(const QJsonObject &newAdditionalProperties)
{
    mAdditionalProperties = newAdditionalProperties;
}
