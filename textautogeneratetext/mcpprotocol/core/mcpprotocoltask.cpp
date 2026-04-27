/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltask.h"
#include <QDebug>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolTask::McpProtocolTask() = default;

McpProtocolTask::~McpProtocolTask() = default;

bool McpProtocolTask::operator==(const McpProtocolTask &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolTask &t)
{
    d.space() << "createdAt" << t.createdAt();
    d.space() << "lastUpdatedAt" << t.lastUpdatedAt();
    d.space() << "pollInterval" << t.pollInterval();
    d.space() << "status" << convertTaskStatusToString(t.status());
    d.space() << "statusMessage" << t.statusMessage();
    d.space() << "taskId" << t.taskId();
    d.space() << "ttl" << t.ttl();

    return d;
}

McpProtocolTask McpProtocolTask::fromJson(const QJsonObject &obj)
{
    McpProtocolTask text;
    text.setCreatedAt(obj.value("createdAt"_L1).toString());
    text.setLastUpdatedAt(obj.value("lastUpdatedAt"_L1).toString());
    if (obj.contains("pollInterval"_L1)) {
        text.setPollInterval(obj.value("pollInterval"_L1).toInt());
    }
    if (obj.contains("status"_L1) && obj["status"_L1].isString()) {
        text.setStatus(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertTaskStatusFromString(obj["status"_L1].toString()));
    }
    if (obj.contains("statusMessage"_L1)) {
        text.setStatusMessage(obj.value("statusMessage"_L1).toString());
    }
    text.setTaskId(obj.value("taskId"_L1).toString());
    if (!obj["ttl"_L1].isNull()) {
        text.setTtl(obj.value("ttl"_L1).toInt());
    }
    return text;
}

QJsonObject McpProtocolTask::toJson(const McpProtocolTask &text)
{
    QJsonObject obj;
    obj["createdAt"_L1] = text.createdAt();
    obj["lastUpdatedAt"_L1] = text.lastUpdatedAt();
    obj["status"_L1] = convertTaskStatusToString(text.status());
    obj["taskId"_L1] = text.taskId();
    if (text.pollInterval().has_value()) {
        obj["pollInterval"_L1] = *text.pollInterval();
    }
    if (text.statusMessage().has_value()) {
        obj["statusMessage"_L1] = *text.statusMessage();
    }
    if (text.ttl().has_value()) {
        obj["ttl"_L1] = *text.ttl();
    } else {
        obj["ttl"_L1] = QJsonValue::Null;
    }
    return obj;
}

QString McpProtocolTask::createdAt() const
{
    return mCreatedAt;
}

void McpProtocolTask::setCreatedAt(const QString &newCreatedAt)
{
    mCreatedAt = newCreatedAt;
}

QString McpProtocolTask::lastUpdatedAt() const
{
    return mLastUpdatedAt;
}

void McpProtocolTask::setLastUpdatedAt(const QString &newLastUpdatedAt)
{
    mLastUpdatedAt = newLastUpdatedAt;
}

std::optional<int> McpProtocolTask::pollInterval() const
{
    return mPollInterval;
}

void McpProtocolTask::setPollInterval(std::optional<int> newPollInterval)
{
    mPollInterval = std::move(newPollInterval);
}

McpProtocolUtils::TaskStatus McpProtocolTask::status() const
{
    return mStatus;
}

void McpProtocolTask::setStatus(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::TaskStatus newStatus)
{
    mStatus = newStatus;
}

std::optional<QString> McpProtocolTask::statusMessage() const
{
    return mStatusMessage;
}

void McpProtocolTask::setStatusMessage(std::optional<QString> newStatusMessage)
{
    mStatusMessage = std::move(newStatusMessage);
}

QString McpProtocolTask::taskId() const
{
    return mTaskId;
}

void McpProtocolTask::setTaskId(const QString &newTaskId)
{
    mTaskId = newTaskId;
}

std::optional<int> McpProtocolTask::ttl() const
{
    return mTtl;
}

void McpProtocolTask::setTtl(std::optional<int> newTtl)
{
    mTtl = newTtl;
}
