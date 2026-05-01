/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolsetlevelrequestparams.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSetLevelRequestParams::McpProtocolSetLevelRequestParams() = default;

McpProtocolSetLevelRequestParams::~McpProtocolSetLevelRequestParams() = default;

bool McpProtocolSetLevelRequestParams::operator==(const McpProtocolSetLevelRequestParams &other) const = default;
bool McpProtocolSetLevelRequestParams::Meta::operator==(const McpProtocolSetLevelRequestParams::Meta &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSetLevelRequestParams &t)
{
    d.space() << "level:" << McpProtocolUtils::convertLoggingLevelToString(t.level());
    d.space() << "meta:" << t.meta();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSetLevelRequestParams::Meta &t)
{
    d.space() << "meta:" << t.progressToken();
    return d;
}

McpProtocolSetLevelRequestParams::Meta McpProtocolSetLevelRequestParams::Meta::fromJson(const QJsonObject &obj)
{
    McpProtocolSetLevelRequestParams::Meta meta;
    if (obj.contains("progressToken"_L1)) {
        meta.setProgressToken(McpProtocolUtils::progressTokenFromJson(obj["progressToken"_L1].toObject()));
    }
    return meta;
}

QJsonObject McpProtocolSetLevelRequestParams::Meta::toJson(const McpProtocolSetLevelRequestParams::Meta &image)
{
    QJsonObject obj;
    if (image.progressToken().has_value()) {
        obj["progressToken"_L1] = McpProtocolUtils::progressTokenToJson(*image.progressToken());
    }
    return obj;
}

McpProtocolSetLevelRequestParams McpProtocolSetLevelRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolSetLevelRequestParams prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolSetLevelRequestParams::Meta::fromJson(obj["_meta"_L1].toObject()));
    }
    if (obj.contains("level"_L1) && obj["level"_L1].isString()) {
        prompt.setLevel(McpProtocolUtils::convertLoggingLevelFromString(obj["level"_L1].toString()));
    }
    return prompt;
}

QJsonObject McpProtocolSetLevelRequestParams::toJson(const McpProtocolSetLevelRequestParams &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolSetLevelRequestParams::Meta::toJson(*boolean.meta());
    }
    obj["level"_L1] = McpProtocolUtils::convertLoggingLevelToString(boolean.level());
    return obj;
}

std::optional<McpProtocolSetLevelRequestParams::Meta> McpProtocolSetLevelRequestParams::meta() const
{
    return mMeta;
}

void McpProtocolSetLevelRequestParams::setMeta(std::optional<Meta> newMeta)
{
    mMeta = std::move(newMeta);
}

McpProtocolUtils::LoggingLevel McpProtocolSetLevelRequestParams::level() const
{
    return mLevel;
}

void McpProtocolSetLevelRequestParams::setLevel(McpProtocolUtils::LoggingLevel newLevel)
{
    mLevel = newLevel;
}

std::optional<McpProtocolUtils::ProgressToken> McpProtocolSetLevelRequestParams::Meta::progressToken() const
{
    return mProgressToken;
}

void McpProtocolSetLevelRequestParams::Meta::setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken)
{
    mProgressToken = std::move(newProgressToken);
}
