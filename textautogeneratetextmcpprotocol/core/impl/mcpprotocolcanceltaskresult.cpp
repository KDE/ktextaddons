/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcanceltaskresult.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>
#include <utility>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolCancelTaskResult::McpProtocolCancelTaskResult() = default;

bool McpProtocolCancelTaskResult::operator==(const McpProtocolCancelTaskResult &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCancelTaskResult &t)
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

McpProtocolCancelTaskResult McpProtocolCancelTaskResult::fromJson(const QJsonObject &obj)
{
    const QJsonValue createdAtValue = obj.value("createdAt"_L1);
    if (!createdAtValue.isString()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolCancelTaskResult: missing required field 'createdAt'";
        return {};
    }
    const QJsonValue lastUpdatedAtValue = obj.value("lastUpdatedAt"_L1);
    if (!lastUpdatedAtValue.isString()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolCancelTaskResult: missing required field 'lastUpdatedAt'";
        return {};
    }
    const QJsonValue statusValue = obj.value("status"_L1);
    if (!statusValue.isString()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolCancelTaskResult: missing required field 'status'";
        return {};
    }
    const McpProtocolUtils::TaskStatus status = McpProtocolUtils::convertTaskStatusFromString(statusValue.toString());
    if (status == McpProtocolUtils::TaskStatus::Unknown) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolCancelTaskResult: invalid field 'status'" << statusValue.toString();
        return {};
    }
    const QJsonValue taskIdValue = obj.value("taskId"_L1);
    if (!taskIdValue.isString()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolCancelTaskResult: missing required field 'taskId'";
        return {};
    }
    // ttl is required but nullable
    const QJsonValue ttlValue = obj.value("ttl"_L1);
    if (!ttlValue.isDouble() && !ttlValue.isNull()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolCancelTaskResult: missing required field 'ttl'";
        return {};
    }
    McpProtocolCancelTaskResult result;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        result.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    result.setCreatedAt(createdAtValue.toString());
    result.setLastUpdatedAt(lastUpdatedAtValue.toString());
    if (const QJsonValue pollIntervalValue = obj.value("pollInterval"_L1); pollIntervalValue.isDouble()) {
        result.setPollInterval(pollIntervalValue.toInteger());
    }
    result.setStatus(status);
    if (obj.contains("statusMessage"_L1)) {
        result.setStatusMessage(obj.value("statusMessage"_L1).toString());
    }
    result.setTaskId(taskIdValue.toString());
    if (ttlValue.isDouble()) {
        result.setTtl(ttlValue.toInteger());
    }
    return result;
}

QJsonObject McpProtocolCancelTaskResult::toJson(const McpProtocolCancelTaskResult &result)
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

std::optional<McpProtocolMeta> McpProtocolCancelTaskResult::meta() const
{
    return mMeta;
}

void McpProtocolCancelTaskResult::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

QString McpProtocolCancelTaskResult::createdAt() const
{
    return mCreatedAt;
}

void McpProtocolCancelTaskResult::setCreatedAt(const QString &newCreatedAt)
{
    mCreatedAt = newCreatedAt;
}

QString McpProtocolCancelTaskResult::lastUpdatedAt() const
{
    return mLastUpdatedAt;
}

void McpProtocolCancelTaskResult::setLastUpdatedAt(const QString &newLastUpdatedAt)
{
    mLastUpdatedAt = newLastUpdatedAt;
}

std::optional<qint64> McpProtocolCancelTaskResult::pollInterval() const
{
    return mPollInterval;
}

void McpProtocolCancelTaskResult::setPollInterval(std::optional<qint64> newPollInterval)
{
    mPollInterval = newPollInterval;
}

McpProtocolUtils::TaskStatus McpProtocolCancelTaskResult::status() const
{
    return mStatus;
}

void McpProtocolCancelTaskResult::setStatus(McpProtocolUtils::TaskStatus newStatus)
{
    mStatus = newStatus;
}

std::optional<QString> McpProtocolCancelTaskResult::statusMessage() const
{
    return mStatusMessage;
}

void McpProtocolCancelTaskResult::setStatusMessage(std::optional<QString> newStatusMessage)
{
    mStatusMessage = std::move(newStatusMessage);
}

QString McpProtocolCancelTaskResult::taskId() const
{
    return mTaskId;
}

void McpProtocolCancelTaskResult::setTaskId(const QString &newTaskId)
{
    mTaskId = newTaskId;
}

std::optional<qint64> McpProtocolCancelTaskResult::ttl() const
{
    return mTtl;
}

void McpProtocolCancelTaskResult::setTtl(std::optional<qint64> newTtl)
{
    mTtl = newTtl;
}
