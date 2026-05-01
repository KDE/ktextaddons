/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolreadresourcerequestparams.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolReadResourceRequestParams::McpProtocolReadResourceRequestParams() = default;

McpProtocolReadResourceRequestParams::~McpProtocolReadResourceRequestParams() = default;

bool McpProtocolReadResourceRequestParams::operator==(const McpProtocolReadResourceRequestParams &other) const = default;
bool McpProtocolReadResourceRequestParams::Meta::operator==(const McpProtocolReadResourceRequestParams::Meta &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolReadResourceRequestParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "uri:" << t.uri();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolReadResourceRequestParams::Meta &t)
{
    d.space() << "progressToken:" << t.progressToken();
    return d;
}

McpProtocolReadResourceRequestParams::Meta McpProtocolReadResourceRequestParams::Meta::fromJson(const QJsonObject &obj)
{
    McpProtocolReadResourceRequestParams::Meta meta;
    if (obj.contains("progressToken"_L1)) {
        meta.setProgressToken(McpProtocolUtils::progressTokenFromJson(obj["progressToken"_L1].toObject()));
    }
    return meta;
}

QJsonObject McpProtocolReadResourceRequestParams::Meta::toJson(const McpProtocolReadResourceRequestParams::Meta &image)
{
    QJsonObject obj;
    if (image.progressToken().has_value()) {
        obj["progressToken"_L1] = McpProtocolUtils::progressTokenToJson(*image.progressToken());
    }
    return obj;
}

McpProtocolReadResourceRequestParams McpProtocolReadResourceRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolReadResourceRequestParams prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolReadResourceRequestParams::Meta::fromJson(obj["_meta"_L1].toObject()));
    }
    prompt.setUri(obj.value("uri"_L1).toString());
    return prompt;
}

QJsonObject McpProtocolReadResourceRequestParams::toJson(const McpProtocolReadResourceRequestParams &boolean)
{
    QJsonObject obj;
    obj["uri"_L1] = boolean.uri();
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolReadResourceRequestParams::Meta::toJson(*boolean.meta());
    }
    return obj;
}

std::optional<McpProtocolReadResourceRequestParams::Meta> McpProtocolReadResourceRequestParams::meta() const
{
    return mMeta;
}

void McpProtocolReadResourceRequestParams::setMeta(std::optional<Meta> newMeta)
{
    mMeta = std::move(newMeta);
}

QString McpProtocolReadResourceRequestParams::uri() const
{
    return mUri;
}

void McpProtocolReadResourceRequestParams::setUri(const QString &newUri)
{
    mUri = newUri;
}

std::optional<McpProtocolUtils::ProgressToken> McpProtocolReadResourceRequestParams::Meta::progressToken() const
{
    return mProgressToken;
}

void McpProtocolReadResourceRequestParams::Meta::setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken)
{
    mProgressToken = std::move(newProgressToken);
}
