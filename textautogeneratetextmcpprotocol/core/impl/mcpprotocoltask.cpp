/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltask.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolTask::McpProtocolTask() = default;

bool McpProtocolTask::operator==(const McpProtocolTask &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolTask &t)
{
    d.space() << "createdAt:" << t.createdAt();
    d.space() << "lastUpdatedAt:" << t.lastUpdatedAt();
    d.space() << "pollInterval:" << t.pollInterval();
    d.space() << "status:" << convertTaskStatusToString(t.status());
    d.space() << "statusMessage:" << t.statusMessage();
    d.space() << "taskId:" << t.taskId();
    d.space() << "ttl:" << t.ttl();

    return d;
}

McpProtocolTask McpProtocolTask::fromJson(const QJsonObject &obj)
{
    McpProtocolTask text;
    if (const QJsonValue createdAtValue = obj.value("createdAt"_L1); createdAtValue.isString()) {
        text.setCreatedAt(createdAtValue.toString());
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolTask: missing required field 'createdAt'";
        return {};
    }
    if (const QJsonValue lastUpdatedAtValue = obj.value("lastUpdatedAt"_L1); lastUpdatedAtValue.isString()) {
        text.setLastUpdatedAt(lastUpdatedAtValue.toString());
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolTask: missing required field 'lastUpdatedAt'";
        return {};
    }
    if (const QJsonValue pollIntervalValue = obj.value("pollInterval"_L1); pollIntervalValue.isDouble()) {
        text.setPollInterval(pollIntervalValue.toInteger());
    }
    if (const QJsonValue statusValue = obj.value("status"_L1); statusValue.isString()) {
        const McpProtocolUtils::TaskStatus status = McpProtocolUtils::convertTaskStatusFromString(statusValue.toString());
        if (status == McpProtocolUtils::TaskStatus::Unknown) {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolTask: invalid field 'status'" << statusValue.toString();
            return {};
        }
        text.setStatus(status);
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolTask: missing required field 'status'";
        return {};
    }
    if (obj.contains("statusMessage"_L1)) {
        text.setStatusMessage(obj.value("statusMessage"_L1).toString());
    }
    if (const QJsonValue taskIdValue = obj.value("taskId"_L1); taskIdValue.isString()) {
        text.setTaskId(taskIdValue.toString());
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolTask: missing required field 'taskId'";
        return {};
    }
    if (const QJsonValue ttlValue = obj.value("ttl"_L1); ttlValue.isDouble()) {
        text.setTtl(ttlValue.toInteger());
    }
    return text;
}

bool McpProtocolTask::isValid() const
{
    return !mTaskId.isEmpty() && !mCreatedAt.isEmpty() && !mLastUpdatedAt.isEmpty() && mStatus != McpProtocolUtils::TaskStatus::Unknown;
}

QJsonObject McpProtocolTask::toJson(const McpProtocolTask &text)
{
    QJsonObject obj;
    obj["createdAt"_L1] = text.createdAt();
    obj["lastUpdatedAt"_L1] = text.lastUpdatedAt();
    // Unknown value is not valid, don't write it
    if (text.status() != McpProtocolUtils::TaskStatus::Unknown) {
        obj["status"_L1] = convertTaskStatusToString(text.status());
    }
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

std::optional<qint64> McpProtocolTask::pollInterval() const
{
    return mPollInterval;
}

void McpProtocolTask::setPollInterval(std::optional<qint64> newPollInterval)
{
    mPollInterval = newPollInterval;
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

std::optional<qint64> McpProtocolTask::ttl() const
{
    return mTtl;
}

void McpProtocolTask::setTtl(std::optional<qint64> newTtl)
{
    mTtl = newTtl;
}
