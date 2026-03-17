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
    return d;
}

McpProtocolLoggingMessageNotificationParams McpProtocolLoggingMessageNotificationParams::fromJson(const QJsonObject &obj)
{
    return {};
}

QJsonObject McpProtocolLoggingMessageNotificationParams::toJson(const McpProtocolLoggingMessageNotificationParams &choice)
{
    QJsonObject obj;
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

#include "moc_mcpprotocolloggingmessagenotificationparams.cpp"
