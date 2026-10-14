/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolloggingmessagenotificationparams.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolLoggingMessageNotificationParams::McpProtocolLoggingMessageNotificationParams() = default;

bool McpProtocolLoggingMessageNotificationParams::operator==(const McpProtocolLoggingMessageNotificationParams &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolLoggingMessageNotificationParams &t)
{
    d.space() << "data:" << t.data();
    d.space() << "logger:" << t.logger();
    d.space() << "level:" << TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertLoggingLevelToString(t.level());
    d.space() << "meta:" << t.meta();
    return d;
}

bool McpProtocolLoggingMessageNotificationParams::isValid() const
{
    return mLevel != McpProtocolUtils::LoggingLevel::Unknown && !mData.isUndefined();
}

McpProtocolLoggingMessageNotificationParams McpProtocolLoggingMessageNotificationParams::fromJson(const QJsonObject &obj)
{
    McpProtocolLoggingMessageNotificationParams params;
    // data is required but can be any JSON value (including null)
    if (!obj.contains("data"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolLoggingMessageNotificationParams: missing required field 'data'";
        return {};
    }
    params.setData(obj.value("data"_L1));
    if (const QJsonValue levelValue = obj.value("level"_L1); levelValue.isString()) {
        const McpProtocolUtils::LoggingLevel level = McpProtocolUtils::convertLoggingLevelFromString(levelValue.toString());
        if (level == McpProtocolUtils::LoggingLevel::Unknown) {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolLoggingMessageNotificationParams: invalid field 'level'" << levelValue.toString();
            return {};
        }
        params.setLevel(level);
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolLoggingMessageNotificationParams: missing required field 'level'";
        return {};
    }
    if (const QJsonValue loggerValue = obj.value("logger"_L1); loggerValue.isString()) {
        params.setLogger(loggerValue.toString());
    }
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        params.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    return params;
}

QJsonObject McpProtocolLoggingMessageNotificationParams::toJson(const McpProtocolLoggingMessageNotificationParams &params)
{
    QJsonObject obj;
    obj["data"_L1] = params.data().isUndefined() ? QJsonValue::Null : params.data();
    // Unknown value is not valid, don't write it
    if (params.level() != McpProtocolUtils::LoggingLevel::Unknown) {
        obj["level"_L1] = TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertLoggingLevelToString(params.level());
    }
    if (params.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*params.meta());
    }
    if (params.logger().has_value()) {
        obj["logger"_L1] = *params.logger();
    }
    return obj;
}

QJsonValue McpProtocolLoggingMessageNotificationParams::data() const
{
    return mData;
}

void McpProtocolLoggingMessageNotificationParams::setData(QJsonValue newData)
{
    mData = std::move(newData);
}

McpProtocolUtils::LoggingLevel McpProtocolLoggingMessageNotificationParams::level() const
{
    return mLevel;
}

void McpProtocolLoggingMessageNotificationParams::setLevel(McpProtocolUtils::LoggingLevel newLevel)
{
    mLevel = newLevel;
}

std::optional<QString> McpProtocolLoggingMessageNotificationParams::logger() const
{
    return mLogger;
}

void McpProtocolLoggingMessageNotificationParams::setLogger(std::optional<QString> newLogger)
{
    mLogger = std::move(newLogger);
}

std::optional<McpProtocolMeta> McpProtocolLoggingMessageNotificationParams::meta() const
{
    return mMeta;
}

void McpProtocolLoggingMessageNotificationParams::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}
