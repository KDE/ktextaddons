/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolsetlevelrequestparams.h"
#include <QDebug>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSetLevelRequestParams::McpProtocolSetLevelRequestParams() = default;

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
    d.space() << "progressToken:" << t.progressToken();
    d.space() << "additionalProperties:" << t.additionalProperties();
    return d;
}

McpProtocolSetLevelRequestParams::Meta McpProtocolSetLevelRequestParams::Meta::fromJson(const QJsonObject &obj)
{
    McpProtocolSetLevelRequestParams::Meta meta;
    if (obj.contains("progressToken"_L1)) {
        meta.setProgressToken(McpProtocolUtils::progressTokenFromJson(obj["progressToken"_L1]));
    }
    QJsonObject additionalProperties = obj;
    additionalProperties.remove("progressToken"_L1);
    meta.setAdditionalProperties(additionalProperties);
    return meta;
}

QJsonObject McpProtocolSetLevelRequestParams::Meta::toJson(const McpProtocolSetLevelRequestParams::Meta &meta)
{
    QJsonObject obj = meta.additionalProperties();
    if (meta.progressToken().has_value()) {
        obj["progressToken"_L1] = McpProtocolUtils::progressTokenToJson(*meta.progressToken());
    }
    return obj;
}

McpProtocolSetLevelRequestParams McpProtocolSetLevelRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolSetLevelRequestParams prompt;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        prompt.setMeta(McpProtocolSetLevelRequestParams::Meta::fromJson(metaValue.toObject()));
    }
    if (const QJsonValue levelValue = obj.value("level"_L1); levelValue.isString()) {
        prompt.setLevel(McpProtocolUtils::convertLoggingLevelFromString(levelValue.toString()));
    }
    return prompt;
}

QJsonObject McpProtocolSetLevelRequestParams::toJson(const McpProtocolSetLevelRequestParams &setLevelRequestParams)
{
    QJsonObject obj;
    if (setLevelRequestParams.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolSetLevelRequestParams::Meta::toJson(*setLevelRequestParams.meta());
    }
    if (setLevelRequestParams.level() != McpProtocolUtils::LoggingLevel::Unknown) {
        obj["level"_L1] = McpProtocolUtils::convertLoggingLevelToString(setLevelRequestParams.level());
    }
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

QJsonObject McpProtocolSetLevelRequestParams::Meta::additionalProperties() const
{
    return mAdditionalProperties;
}

void McpProtocolSetLevelRequestParams::Meta::setAdditionalProperties(const QJsonObject &newAdditionalProperties)
{
    mAdditionalProperties = newAdditionalProperties;
}
