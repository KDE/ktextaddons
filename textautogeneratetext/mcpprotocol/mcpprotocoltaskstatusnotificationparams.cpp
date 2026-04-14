/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltaskstatusnotificationparams.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolTaskStatusNotificationParams::McpProtocolTaskStatusNotificationParams() = default;

McpProtocolTaskStatusNotificationParams::~McpProtocolTaskStatusNotificationParams() = default;

bool McpProtocolTaskStatusNotificationParams::operator==(const McpProtocolTaskStatusNotificationParams &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolTaskStatusNotificationParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "createdAt:" << t.createdAt();
    d.space() << "lastUpdatedAt:" << t.lastUpdatedAt();
    d.space() << "pollInterval:" << t.pollInterval();
    d.space() << "statusMessage:" << t.statusMessage();
    d.space() << "taskId:" << t.taskId();
    d.space() << "status:" << McpProtocolUtils::convertTaskStatusToString(t.status());
    d.space() << "ttl:" << t.ttl();
    return d;
}

McpProtocolTaskStatusNotificationParams McpProtocolTaskStatusNotificationParams::fromJson(const QJsonObject &obj)
{
    McpProtocolTaskStatusNotificationParams prompt;
    prompt.setCreatedAt(obj.value("createdAt"_L1).toString());
    prompt.setLastUpdatedAt(obj.value("lastUpdatedAt"_L1).toString());
    if (obj.contains("pollInterval"_L1)) {
        prompt.setPollInterval(obj.value("pollInterval"_L1).toInt());
    }
    if (obj.contains("status"_L1) && obj["status"_L1].isString()) {
        prompt.setStatus(McpProtocolUtils::convertTaskStatusFromString(obj["status"_L1].toString()));
    }
    if (obj.contains("statusMessage"_L1)) {
        prompt.setStatusMessage(obj.value("statusMessage"_L1).toString());
    }
    prompt.setTaskId(obj.value("taskId"_L1).toString());
    if (!obj["ttl"_L1].isNull()) {
        prompt.setTtl(obj.value("ttl"_L1).toInt());
    }
    return prompt;
}

QJsonObject McpProtocolTaskStatusNotificationParams::toJson(const McpProtocolTaskStatusNotificationParams &boolean)
{
    QJsonObject obj;
    obj["createdAt"_L1] = boolean.createdAt();
    obj["lastUpdatedAt"_L1] = boolean.lastUpdatedAt();
    obj["status"_L1] = McpProtocolUtils::convertTaskStatusToString(boolean.status());
    obj["taskId"_L1] = boolean.taskId();
    if (boolean.pollInterval().has_value()) {
        obj.insert("pollInterval"_L1, *boolean.pollInterval());
    }
    if (boolean.statusMessage().has_value()) {
        obj.insert("statusMessage"_L1, *boolean.statusMessage());
    }
    if (boolean.ttl().has_value()) {
        obj.insert("ttl"_L1, *boolean.ttl());
    } else {
        obj.insert("ttl"_L1, QJsonValue::Null);
    }
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolTaskStatusNotificationParams::meta() const
{
    return mMeta;
}

void McpProtocolTaskStatusNotificationParams::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

QString McpProtocolTaskStatusNotificationParams::createdAt() const
{
    return mCreatedAt;
}

void McpProtocolTaskStatusNotificationParams::setCreatedAt(const QString &newCreatedAt)
{
    mCreatedAt = newCreatedAt;
}

QString McpProtocolTaskStatusNotificationParams::lastUpdatedAt() const
{
    return mLastUpdatedAt;
}

void McpProtocolTaskStatusNotificationParams::setLastUpdatedAt(const QString &newLastUpdatedAt)
{
    mLastUpdatedAt = newLastUpdatedAt;
}

std::optional<int> McpProtocolTaskStatusNotificationParams::pollInterval() const
{
    return mPollInterval;
}

void McpProtocolTaskStatusNotificationParams::setPollInterval(std::optional<int> newPollInterval)
{
    mPollInterval = newPollInterval;
}

McpProtocolUtils::TaskStatus McpProtocolTaskStatusNotificationParams::status() const
{
    return mStatus;
}

void McpProtocolTaskStatusNotificationParams::setStatus(McpProtocolUtils::TaskStatus newStatus)
{
    mStatus = newStatus;
}

std::optional<QString> McpProtocolTaskStatusNotificationParams::statusMessage() const
{
    return mStatusMessage;
}

void McpProtocolTaskStatusNotificationParams::setStatusMessage(std::optional<QString> newStatusMessage)
{
    mStatusMessage = std::move(newStatusMessage);
}

QString McpProtocolTaskStatusNotificationParams::taskId() const
{
    return mTaskId;
}

void McpProtocolTaskStatusNotificationParams::setTaskId(const QString &newTaskId)
{
    mTaskId = newTaskId;
}

std::optional<int> McpProtocolTaskStatusNotificationParams::ttl() const
{
    return mTtl;
}

void McpProtocolTaskStatusNotificationParams::setTtl(std::optional<int> newTtl)
{
    mTtl = newTtl;
}
