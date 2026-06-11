/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcanceltaskresult.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolCancelTaskResult::McpProtocolCancelTaskResult() = default;

McpProtocolCancelTaskResult::~McpProtocolCancelTaskResult() = default;

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
    McpProtocolCancelTaskResult prompt;
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

QJsonObject McpProtocolCancelTaskResult::toJson(const McpProtocolCancelTaskResult &boolean)
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

std::optional<int> McpProtocolCancelTaskResult::pollInterval() const
{
    return mPollInterval;
}

void McpProtocolCancelTaskResult::setPollInterval(std::optional<int> newPollInterval)
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

std::optional<int> McpProtocolCancelTaskResult::ttl() const
{
    return mTtl;
}

void McpProtocolCancelTaskResult::setTtl(std::optional<int> newTtl)
{
    mTtl = newTtl;
}
