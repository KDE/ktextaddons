/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcreatetaskresult.h"
#include <QDebug>
#include <QJsonObject>

#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolCreateTaskResult::McpProtocolCreateTaskResult() = default;

bool McpProtocolCreateTaskResult::operator==(const McpProtocolCreateTaskResult &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateTaskResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "task:" << t.task();
    return d;
}

McpProtocolCreateTaskResult McpProtocolCreateTaskResult::fromJson(const QJsonObject &obj)
{
    McpProtocolCreateTaskResult prompt;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    if (const QJsonValue taskValue = obj.value("task"_L1); taskValue.isObject()) {
        prompt.setTask(McpProtocolTask::fromJson(taskValue.toObject()));
    }
    return prompt;
}

QJsonObject McpProtocolCreateTaskResult::toJson(const McpProtocolCreateTaskResult &boolean)
{
    QJsonObject obj;
    obj["task"_L1] = McpProtocolTask::toJson(boolean.task());
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolCreateTaskResult::meta() const
{
    return mMeta;
}

void McpProtocolCreateTaskResult::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

McpProtocolTask McpProtocolCreateTaskResult::task() const
{
    return mTask;
}

void McpProtocolCreateTaskResult::setTask(const McpProtocolTask &newTask)
{
    mTask = newTask;
}
