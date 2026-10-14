/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolsetlevelrequestparams.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSetLevelRequestParams::McpProtocolSetLevelRequestParams() = default;

bool McpProtocolSetLevelRequestParams::operator==(const McpProtocolSetLevelRequestParams &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSetLevelRequestParams &t)
{
    d.space() << "level:" << McpProtocolUtils::convertLoggingLevelToString(t.level());
    d.space() << "meta:" << t.meta();
    return d;
}

McpProtocolSetLevelRequestParams McpProtocolSetLevelRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolSetLevelRequestParams prompt;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        prompt.setMeta(McpProtocolSetLevelRequestParams::Meta::fromJson(metaValue.toObject()));
    }
    if (const QJsonValue levelValue = obj.value("level"_L1); levelValue.isString()) {
        const McpProtocolUtils::LoggingLevel level = McpProtocolUtils::convertLoggingLevelFromString(levelValue.toString());
        if (level == McpProtocolUtils::LoggingLevel::Unknown) {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolSetLevelRequestParams: invalid field 'level'" << levelValue.toString();
            return {};
        }
        prompt.setLevel(level);
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolSetLevelRequestParams: missing required field 'level'";
        return {};
    }
    return prompt;
}

bool McpProtocolSetLevelRequestParams::isValid() const
{
    return mLevel != McpProtocolUtils::LoggingLevel::Unknown;
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
