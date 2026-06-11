/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolgettaskresult.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolGetTaskResult::McpProtocolGetTaskResult() = default;

McpProtocolGetTaskResult::~McpProtocolGetTaskResult() = default;

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
    McpProtocolGetTaskResult prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
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
    prompt.setCreatedAt(obj.value("createdAt"_L1).toString());
    prompt.setLastUpdatedAt(obj.value("lastUpdatedAt"_L1).toString());
    if (obj.contains("pollInterval"_L1)) {
        prompt.setPollInterval(obj.value("pollInterval"_L1).toInt());
    }
    if (obj.contains("status"_L1) && obj["status"_L1].isString()) {
        prompt.setStatus(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertTaskStatusFromString(obj["status"_L1].toString()));
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

QJsonObject McpProtocolGetTaskResult::toJson(const McpProtocolGetTaskResult &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    obj["createdAt"_L1] = boolean.createdAt();
    obj["lastUpdatedAt"_L1] = boolean.lastUpdatedAt();
    obj["status"_L1] = TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertTaskStatusToString(boolean.status());
    obj["taskId"_L1] = boolean.taskId();
    if (boolean.pollInterval().has_value()) {
        obj["pollInterval"_L1], *boolean.pollInterval();
    }
    if (boolean.statusMessage().has_value()) {
        obj["statusMessage"_L1] = *boolean.statusMessage();
    }
    if (boolean.ttl().has_value()) {
        obj["ttl"_L1], *boolean.ttl();
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

std::optional<int> McpProtocolGetTaskResult::pollInterval() const
{
    return mPollInterval;
}

void McpProtocolGetTaskResult::setPollInterval(std::optional<int> newPollInterval)
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

std::optional<int> McpProtocolGetTaskResult::ttl() const
{
    return mTtl;
}

void McpProtocolGetTaskResult::setTtl(std::optional<int> newTtl)
{
    mTtl = newTtl;
}
