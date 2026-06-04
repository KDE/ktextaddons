/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocollisttasksresult.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolListTasksResult::McpProtocolListTasksResult() = default;

McpProtocolListTasksResult::~McpProtocolListTasksResult() = default;

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
    McpProtocolListTasksResult prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    if (obj.contains("nextCursor"_L1)) {
        prompt.setNextCursor(obj.value("nextCursor"_L1).toString());
    }
    if (obj.contains("tasks"_L1) && obj["tasks"_L1].isArray()) {
        const QJsonArray arr = obj["tasks"_L1].toArray();
        QList<McpProtocolTask> tasks;
        for (const auto &v : arr) {
            tasks.append(McpProtocolTask::fromJson(v.toObject()));
        }
        prompt.setTasks(tasks);
    }
    return prompt;
}

QJsonObject McpProtocolListTasksResult::toJson(const McpProtocolListTasksResult &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    if (boolean.nextCursor().has_value()) {
        obj["nextCursor"_L1] = *boolean.nextCursor();
    }
    QJsonArray arr_tasks;
    for (const auto &v : boolean.tasks()) {
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

void McpProtocolListTasksResult::setTasks(const QList<McpProtocolTask> &newTasks)
{
    mTasks = newTasks;
}
