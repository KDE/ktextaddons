/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolsubscriberequestparams.h"
#include <QDebug>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSubscribeRequestParams::McpProtocolSubscribeRequestParams() = default;

bool McpProtocolSubscribeRequestParams::operator==(const McpProtocolSubscribeRequestParams &other) const = default;
bool McpProtocolSubscribeRequestParams::Meta::operator==(const McpProtocolSubscribeRequestParams::Meta &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscribeRequestParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "uri:" << t.uri();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscribeRequestParams::Meta &t)
{
    d.space() << "progressToken:" << t.progressToken();
    d.space() << "additionalProperties:" << t.additionalProperties();
    return d;
}

McpProtocolSubscribeRequestParams::Meta McpProtocolSubscribeRequestParams::Meta::fromJson(const QJsonObject &obj)
{
    McpProtocolSubscribeRequestParams::Meta meta;
    if (obj.contains("progressToken"_L1)) {
        meta.setProgressToken(McpProtocolUtils::progressTokenFromJson(obj["progressToken"_L1]));
    }
    QJsonObject additionalProperties = obj;
    additionalProperties.remove("progressToken"_L1);
    meta.setAdditionalProperties(additionalProperties);
    return meta;
}

QJsonObject McpProtocolSubscribeRequestParams::Meta::toJson(const McpProtocolSubscribeRequestParams::Meta &meta)
{
    QJsonObject obj = meta.additionalProperties();
    if (meta.progressToken().has_value()) {
        obj["progressToken"_L1] = McpProtocolUtils::progressTokenToJson(*meta.progressToken());
    }
    return obj;
}

McpProtocolSubscribeRequestParams McpProtocolSubscribeRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolSubscribeRequestParams prompt;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        prompt.setMeta(McpProtocolSubscribeRequestParams::Meta::fromJson(metaValue.toObject()));
    }
    prompt.setUri(obj.value("uri"_L1).toString());
    return prompt;
}

QJsonObject McpProtocolSubscribeRequestParams::toJson(const McpProtocolSubscribeRequestParams &subscribeRequestParams)
{
    QJsonObject obj;
    obj["uri"_L1] = subscribeRequestParams.uri();
    if (subscribeRequestParams.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolSubscribeRequestParams::Meta::toJson(*subscribeRequestParams.meta());
    }
    return obj;
}

std::optional<McpProtocolSubscribeRequestParams::Meta> McpProtocolSubscribeRequestParams::meta() const
{
    return mMeta;
}

void McpProtocolSubscribeRequestParams::setMeta(std::optional<Meta> newMeta)
{
    mMeta = std::move(newMeta);
}

QString McpProtocolSubscribeRequestParams::uri() const
{
    return mUri;
}

void McpProtocolSubscribeRequestParams::setUri(const QString &newUri)
{
    mUri = newUri;
}

std::optional<McpProtocolUtils::ProgressToken> McpProtocolSubscribeRequestParams::Meta::progressToken() const
{
    return mProgressToken;
}

void McpProtocolSubscribeRequestParams::Meta::setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken)
{
    mProgressToken = std::move(newProgressToken);
}

QJsonObject McpProtocolSubscribeRequestParams::Meta::additionalProperties() const
{
    return mAdditionalProperties;
}

void McpProtocolSubscribeRequestParams::Meta::setAdditionalProperties(const QJsonObject &newAdditionalProperties)
{
    mAdditionalProperties = newAdditionalProperties;
}
