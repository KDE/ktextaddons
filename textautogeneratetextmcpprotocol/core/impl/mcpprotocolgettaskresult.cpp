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
    if (!obj.contains("createdAt"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: createdAt";
        return {};
    }
    if (!obj.contains("lastUpdatedAt"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: lastUpdatedAt";
        return {};
    }
    if (!obj.contains("status"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: status";
        return {};
    }
    if (!obj.contains("taskId"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: taskId";
        return {};
    }
    if (!obj.contains("ttl"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: ttl";
        return {};
    }
    result.setCreatedAt(obj.value("createdAt"_L1).toString());
    result.setLastUpdatedAt(obj.value("lastUpdatedAt"_L1).toString());
    if (obj.contains("pollInterval"_L1)) {
        result.setPollInterval(obj.value("pollInterval"_L1).toInteger());
    }
    if (const QJsonValue statusValue = obj.value("status"_L1); statusValue.isString()) {
        result.setStatus(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertTaskStatusFromString(statusValue.toString()));
    }
    if (obj.contains("statusMessage"_L1)) {
        result.setStatusMessage(obj.value("statusMessage"_L1).toString());
    }
    result.setTaskId(obj.value("taskId"_L1).toString());
    if (!obj["ttl"_L1].isNull()) {
        result.setTtl(obj.value("ttl"_L1).toInteger());
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
    obj["status"_L1] = TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertTaskStatusToString(result.status());
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
