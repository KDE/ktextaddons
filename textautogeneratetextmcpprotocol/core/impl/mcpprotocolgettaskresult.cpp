/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolgettaskresult.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>
#include <utility>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolGetTaskResult::McpProtocolGetTaskResult() = default;

bool McpProtocolGetTaskResult::operator==(const McpProtocolGetTaskResult &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolGetTaskResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "createdAt:" << t.createdAt();
    d.space() << "lastUpdatedAt:" << t.lastUpdatedAt();
    d.space() << "pollInterval:" << t.pollInterval();
    d.space() << "status:" << TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertTaskStatusToString(t.status());
    d.space() << "statusMessage:" << t.statusMessage();
    d.space() << "taskId:" << t.taskId();
    d.space() << "ttl:" << t.ttl();
    return d;
}

McpProtocolGetTaskResult McpProtocolGetTaskResult::fromJson(const QJsonObject &obj)
{
    McpProtocolGetTaskResult result;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        result.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    if (const QJsonValue createdAtValue = obj.value("createdAt"_L1); createdAtValue.isString()) {
        result.setCreatedAt(createdAtValue.toString());
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolGetTaskResult: missing required field 'createdAt'";
        return {};
    }
    if (const QJsonValue lastUpdatedAtValue = obj.value("lastUpdatedAt"_L1); lastUpdatedAtValue.isString()) {
        result.setLastUpdatedAt(lastUpdatedAtValue.toString());
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolGetTaskResult: missing required field 'lastUpdatedAt'";
        return {};
    }
    if (const QJsonValue statusValue = obj.value("status"_L1); statusValue.isString()) {
        const McpProtocolUtils::TaskStatus status = McpProtocolUtils::convertTaskStatusFromString(statusValue.toString());
        if (status == McpProtocolUtils::TaskStatus::Unknown) {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolGetTaskResult: invalid field 'status'" << statusValue.toString();
            return {};
        }
        result.setStatus(status);
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolGetTaskResult: missing required field 'status'";
        return {};
    }
    if (const QJsonValue taskIdValue = obj.value("taskId"_L1); taskIdValue.isString()) {
        result.setTaskId(taskIdValue.toString());
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolGetTaskResult: missing required field 'taskId'";
        return {};
    }
    // ttl is required but can be null
    if (const QJsonValue ttlValue = obj.value("ttl"_L1); ttlValue.isDouble()) {
        result.setTtl(ttlValue.toInteger());
    } else if (!ttlValue.isNull()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolGetTaskResult: missing required field 'ttl'";
        return {};
    }
    if (const QJsonValue pollIntervalValue = obj.value("pollInterval"_L1); pollIntervalValue.isDouble()) {
        result.setPollInterval(pollIntervalValue.toInteger());
    }
    if (const QJsonValue statusMessageValue = obj.value("statusMessage"_L1); statusMessageValue.isString()) {
        result.setStatusMessage(statusMessageValue.toString());
    }
    return result;
}

QJsonObject McpProtocolGetTaskResult::toJson(const McpProtocolGetTaskResult &result)
{
    QJsonObject obj;
    if (result.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*result.meta());
    }
    obj["createdAt"_L1] = result.createdAt();
    obj["lastUpdatedAt"_L1] = result.lastUpdatedAt();
    // Unknown value is not valid, don't write it
    if (result.status() != McpProtocolUtils::TaskStatus::Unknown) {
        obj["status"_L1] = TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertTaskStatusToString(result.status());
    }
    obj["taskId"_L1] = result.taskId();
    if (result.pollInterval().has_value()) {
        obj["pollInterval"_L1] = *result.pollInterval();
    }
    if (result.statusMessage().has_value()) {
        obj["statusMessage"_L1] = *result.statusMessage();
    }
    if (result.ttl().has_value()) {
        obj["ttl"_L1] = *result.ttl();
    } else {
        obj["ttl"_L1] = QJsonValue::Null;
    }
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolGetTaskResult::meta() const
{
    return mMeta;
}

void McpProtocolGetTaskResult::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

QString McpProtocolGetTaskResult::createdAt() const
{
    return mCreatedAt;
}

void McpProtocolGetTaskResult::setCreatedAt(const QString &newCreatedAt)
{
    mCreatedAt = newCreatedAt;
}

QString McpProtocolGetTaskResult::lastUpdatedAt() const
{
    return mLastUpdatedAt;
}

void McpProtocolGetTaskResult::setLastUpdatedAt(const QString &newLastUpdatedAt)
{
    mLastUpdatedAt = newLastUpdatedAt;
}

std::optional<qint64> McpProtocolGetTaskResult::pollInterval() const
{
    return mPollInterval;
}

void McpProtocolGetTaskResult::setPollInterval(std::optional<qint64> newPollInterval)
{
    mPollInterval = newPollInterval;
}

McpProtocolUtils::TaskStatus McpProtocolGetTaskResult::status() const
{
    return mStatus;
}

void McpProtocolGetTaskResult::setStatus(McpProtocolUtils::TaskStatus newStatus)
{
    mStatus = newStatus;
}

std::optional<QString> McpProtocolGetTaskResult::statusMessage() const
{
    return mStatusMessage;
}

void McpProtocolGetTaskResult::setStatusMessage(std::optional<QString> newStatusMessage)
{
    mStatusMessage = std::move(newStatusMessage);
}

QString McpProtocolGetTaskResult::taskId() const
{
    return mTaskId;
}

void McpProtocolGetTaskResult::setTaskId(const QString &newTaskId)
{
    mTaskId = newTaskId;
}

std::optional<qint64> McpProtocolGetTaskResult::ttl() const
{
    return mTtl;
}

void McpProtocolGetTaskResult::setTtl(std::optional<qint64> newTtl)
{
    mTtl = newTtl;
}
