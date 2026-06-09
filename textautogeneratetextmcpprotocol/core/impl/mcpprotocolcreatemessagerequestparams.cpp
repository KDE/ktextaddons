/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcreatemessagerequestparams.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolCreateMessageRequestParams::McpProtocolCreateMessageRequestParams() = default;

McpProtocolCreateMessageRequestParams::~McpProtocolCreateMessageRequestParams() = default;

// TODO bool McpProtocolCreateMessageRequestParams::operator==(const McpProtocolCreateMessageRequestParams &other) const = default;
bool McpProtocolCreateMessageRequestParams::Meta::operator==(const McpProtocolCreateMessageRequestParams::Meta &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequestParams &t)
{
    d.space() << "meta:" << t.meta();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequestParams::Meta &t)
{
    d.space() << "progressToken:" << t.progressToken();
    return d;
}

McpProtocolCreateMessageRequestParams::Meta McpProtocolCreateMessageRequestParams::Meta::fromJson(const QJsonObject &obj)
{
    McpProtocolCreateMessageRequestParams::Meta meta;
    if (obj.contains("progressToken"_L1)) {
        meta.setProgressToken(McpProtocolUtils::progressTokenFromJson(obj["progressToken"_L1]));
    }
    return meta;
}

QJsonObject McpProtocolCreateMessageRequestParams::Meta::toJson(const McpProtocolCreateMessageRequestParams::Meta &image)
{
    QJsonObject obj;
    if (image.progressToken().has_value()) {
        obj["progressToken"_L1] = McpProtocolUtils::progressTokenToJson(*image.progressToken());
    }
    return obj;
}

McpProtocolCreateMessageRequestParams McpProtocolCreateMessageRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolCreateMessageRequestParams prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolCreateMessageRequestParams::Meta::fromJson(obj["_meta"_L1].toObject()));
    }
    return prompt;
}

QJsonObject McpProtocolCreateMessageRequestParams::toJson(const McpProtocolCreateMessageRequestParams &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolCreateMessageRequestParams::Meta::toJson(*boolean.meta());
    }
    return obj;
}

std::optional<McpProtocolCreateMessageRequestParams::Meta> McpProtocolCreateMessageRequestParams::meta() const
{
    return mMeta;
}

void McpProtocolCreateMessageRequestParams::setMeta(std::optional<Meta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<McpProtocolUtils::ProgressToken> McpProtocolCreateMessageRequestParams::Meta::progressToken() const
{
    return mProgressToken;
}

void McpProtocolCreateMessageRequestParams::Meta::setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken)
{
    mProgressToken = std::move(newProgressToken);
}
