/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolrelatedtaskmetadata.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolRelatedTaskMetadata::McpProtocolRelatedTaskMetadata() = default;

bool McpProtocolRelatedTaskMetadata::operator==(const McpProtocolRelatedTaskMetadata &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolRelatedTaskMetadata &t)
{
    d.space() << "taskId:" << t.taskId();
    return d;
}

McpProtocolRelatedTaskMetadata McpProtocolRelatedTaskMetadata::fromJson(const QJsonObject &obj)
{
    McpProtocolRelatedTaskMetadata task;
    if (const QJsonValue taskIdValue = obj.value("taskId"_L1); taskIdValue.isString() && !taskIdValue.toString().isEmpty()) {
        task.setTaskId(taskIdValue.toString());
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolRelatedTaskMetadata: missing required field 'taskId'";
        return {};
    }
    return task;
}

QJsonObject McpProtocolRelatedTaskMetadata::toJson(const McpProtocolRelatedTaskMetadata &prompt)
{
    QJsonObject obj;
    obj["taskId"_L1] = prompt.taskId();
    return obj;
}

QString McpProtocolRelatedTaskMetadata::taskId() const
{
    return mTaskId;
}

void McpProtocolRelatedTaskMetadata::setTaskId(const QString &newTaskId)
{
    mTaskId = newTaskId;
}
