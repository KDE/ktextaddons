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
    // TODO d.space() << "status:" << t.status();
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
    // TODO
    return prompt;
}

QJsonObject McpProtocolCancelTaskResult::toJson(const McpProtocolCancelTaskResult &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    // TODO
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
