/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocollisttasksresult.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <utility>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolListTasksResult::McpProtocolListTasksResult() = default;

bool McpProtocolListTasksResult::operator==(const McpProtocolListTasksResult &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolListTasksResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "nextCursor:" << t.nextCursor();
    d.space() << "tasks:" << t.tasks();
    return d;
}

McpProtocolListTasksResult McpProtocolListTasksResult::fromJson(const QJsonObject &obj)
{
    McpProtocolListTasksResult result;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        result.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    if (obj.contains("nextCursor"_L1)) {
        result.setNextCursor(obj.value("nextCursor"_L1).toString());
    }
    if (const QJsonValue tasksValue = obj.value("tasks"_L1); tasksValue.isArray()) {
        const QJsonArray arr = tasksValue.toArray();
        QList<McpProtocolTask> tasks;
        tasks.reserve(arr.count());
        for (const auto &v : arr) {
            tasks.append(McpProtocolTask::fromJson(v.toObject()));
        }
        result.setTasks(std::move(tasks));
    }
    return result;
}

QJsonObject McpProtocolListTasksResult::toJson(const McpProtocolListTasksResult &result)
{
    QJsonObject obj;
    if (result.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*result.meta());
    }
    if (result.nextCursor().has_value()) {
        obj["nextCursor"_L1] = *result.nextCursor();
    }
    QJsonArray arr_tasks;
    for (const auto &v : result.tasks()) {
        arr_tasks.append(McpProtocolTask::toJson(v));
    }
    obj["tasks"_L1] = arr_tasks;
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolListTasksResult::meta() const
{
    return mMeta;
}

void McpProtocolListTasksResult::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<QString> McpProtocolListTasksResult::nextCursor() const
{
    return mNextCursor;
}

void McpProtocolListTasksResult::setNextCursor(std::optional<QString> newNextCursor)
{
    mNextCursor = std::move(newNextCursor);
}

QList<McpProtocolTask> McpProtocolListTasksResult::tasks() const
{
    return mTasks;
}

void McpProtocolListTasksResult::setTasks(QList<McpProtocolTask> newTasks)
{
    mTasks = std::move(newTasks);
}
