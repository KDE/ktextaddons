/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltaskstatusnotificationparams.h"
#include <QDebug>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolTaskStatusNotificationParams::McpProtocolTaskStatusNotificationParams() = default;

bool McpProtocolTaskStatusNotificationParams::operator==(const McpProtocolTaskStatusNotificationParams &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolTaskStatusNotificationParams &t)
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
    if (const QJsonValue pollIntervalValue = obj.value("pollInterval"_L1); pollIntervalValue.isDouble()) {
        prompt.setPollInterval(pollIntervalValue.toInteger());
    }
    if (const QJsonValue statusValue = obj.value("status"_L1); statusValue.isString()) {
        prompt.setStatus(McpProtocolUtils::convertTaskStatusFromString(statusValue.toString()));
    }
    if (obj.contains("statusMessage"_L1)) {
        prompt.setStatusMessage(obj.value("statusMessage"_L1).toString());
    }
    prompt.setTaskId(obj.value("taskId"_L1).toString());
    if (const QJsonValue ttlValue = obj.value("ttl"_L1); ttlValue.isDouble()) {
        prompt.setTtl(ttlValue.toInteger());
    }
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    return prompt;
}

QJsonObject McpProtocolTaskStatusNotificationParams::toJson(const McpProtocolTaskStatusNotificationParams &taskStatusNotificationParams)
{
    QJsonObject obj;
    obj["createdAt"_L1] = taskStatusNotificationParams.createdAt();
    obj["lastUpdatedAt"_L1] = taskStatusNotificationParams.lastUpdatedAt();
    // Unknown value is not valid, don't write it
    if (taskStatusNotificationParams.status() != McpProtocolUtils::TaskStatus::Unknown) {
        obj["status"_L1] = McpProtocolUtils::convertTaskStatusToString(taskStatusNotificationParams.status());
    }
    obj["taskId"_L1] = taskStatusNotificationParams.taskId();
    if (taskStatusNotificationParams.pollInterval().has_value()) {
        obj.insert("pollInterval"_L1, *taskStatusNotificationParams.pollInterval());
    }
    if (taskStatusNotificationParams.statusMessage().has_value()) {
        obj.insert("statusMessage"_L1, *taskStatusNotificationParams.statusMessage());
    }
    if (taskStatusNotificationParams.ttl().has_value()) {
        obj.insert("ttl"_L1, *taskStatusNotificationParams.ttl());
    } else {
        obj.insert("ttl"_L1, QJsonValue::Null);
    }
    if (taskStatusNotificationParams.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*taskStatusNotificationParams.meta());
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

std::optional<qint64> McpProtocolTaskStatusNotificationParams::pollInterval() const
{
    return mPollInterval;
}

void McpProtocolTaskStatusNotificationParams::setPollInterval(std::optional<qint64> newPollInterval)
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

std::optional<qint64> McpProtocolTaskStatusNotificationParams::ttl() const
{
    return mTtl;
}

void McpProtocolTaskStatusNotificationParams::setTtl(std::optional<qint64> newTtl)
{
    mTtl = newTtl;
}
