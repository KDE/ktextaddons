/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolloggingmessagenotificationparams.h"
#include <QDebug>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolLoggingMessageNotificationParams::McpProtocolLoggingMessageNotificationParams() = default;

McpProtocolLoggingMessageNotificationParams::~McpProtocolLoggingMessageNotificationParams() = default;

bool McpProtocolLoggingMessageNotificationParams::operator==(const McpProtocolLoggingMessageNotificationParams &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolLoggingMessageNotificationParams &t)
{
    d.space() << "data:" << t.data();
    d.space() << "logger:" << t.logger();
    d.space() << "level:" << McpProtocol::McpProtocolUtils::convertLoggingLevelToString(t.level());
    d.space() << "meta:" << t.meta();
    return d;
}

McpProtocolLoggingMessageNotificationParams McpProtocolLoggingMessageNotificationParams::fromJson(const QJsonObject &obj)
{
    McpProtocolLoggingMessageNotificationParams params;
    params.setData(obj.value("data"_L1).toString());
    if (obj.contains("level"_L1) && obj["level"_L1].isString()) {
        params.setLevel(McpProtocol::McpProtocolUtils::convertLoggingLevelFromString(obj["level"_L1].toString()));
    }
    if (obj.contains("logger"_L1)) {
        params.setLogger(obj.value("logger"_L1).toString());
    }
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        params.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    return params;
}

QJsonObject McpProtocolLoggingMessageNotificationParams::toJson(const McpProtocolLoggingMessageNotificationParams &params)
{
    QJsonObject obj;
    obj["data"_L1] = params.data();
    obj["level"_L1] = McpProtocol::McpProtocolUtils::convertLoggingLevelToString(params.level());
    if (params.meta().has_value()) {
        obj["meta"_L1] = McpProtocolMeta::toJson(*params.meta());
    }
    if (params.logger().has_value()) {
        obj["logger"_L1] = *params.logger();
    }
    return obj;
}

QString McpProtocolLoggingMessageNotificationParams::data() const
{
    return mData;
}

void McpProtocolLoggingMessageNotificationParams::setData(const QString &newData)
{
    mData = newData;
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

#include "moc_mcpprotocolloggingmessagenotificationparams.cpp"
