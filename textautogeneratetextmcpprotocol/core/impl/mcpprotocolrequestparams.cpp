/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolrequestparams.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolRequestParams::McpProtocolRequestParams() = default;

McpProtocolRequestParams::~McpProtocolRequestParams() = default;

bool McpProtocolRequestParams::operator==(const McpProtocolRequestParams &other) const = default;
bool McpProtocolRequestParams::Meta::operator==(const McpProtocolRequestParams::Meta &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolRequestParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "uri:" << t.uri();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolRequestParams::Meta &t)
{
    d.space() << "progressToken:" << t.progressToken();
    return d;
}

McpProtocolRequestParams::Meta McpProtocolRequestParams::Meta::fromJson(const QJsonObject &obj)
{
    McpProtocolRequestParams::Meta meta;
    if (obj.contains("progressToken"_L1)) {
        meta.setProgressToken(McpProtocolUtils::progressTokenFromJson(obj["progressToken"_L1].toObject()));
    }
    return meta;
}

QJsonObject McpProtocolRequestParams::Meta::toJson(const McpProtocolRequestParams::Meta &image)
{
    QJsonObject obj;
    if (image.progressToken().has_value()) {
        obj["progressToken"_L1] = McpProtocolUtils::progressTokenToJson(*image.progressToken());
    }
    return obj;
}

McpProtocolRequestParams McpProtocolRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolRequestParams prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolRequestParams::Meta::fromJson(obj["_meta"_L1].toObject()));
    }
    prompt.setUri(obj.value("uri"_L1).toString());
    return prompt;
}

QJsonObject McpProtocolRequestParams::toJson(const McpProtocolRequestParams &boolean)
{
    QJsonObject obj;
    obj["uri"_L1] = boolean.uri();
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolRequestParams::Meta::toJson(*boolean.meta());
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

QString McpProtocolRequestParams::uri() const
{
    return mUri;
}

void McpProtocolRequestParams::setUri(const QString &newUri)
{
    mUri = newUri;
}

std::optional<McpProtocolUtils::ProgressToken> McpProtocolRequestParams::Meta::progressToken() const
{
    return mProgressToken;
}

void McpProtocolRequestParams::Meta::setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken)
{
    mProgressToken = std::move(newProgressToken);
}
