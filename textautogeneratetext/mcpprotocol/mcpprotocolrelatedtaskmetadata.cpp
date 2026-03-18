/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolrelatedtaskmetadata.h"
#include <QDebug>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolRelatedTaskMetadata::McpProtocolRelatedTaskMetadata() = default;

McpProtocolRelatedTaskMetadata::~McpProtocolRelatedTaskMetadata() = default;

bool McpProtocolRelatedTaskMetadata::operator==(const McpProtocolRelatedTaskMetadata &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolRelatedTaskMetadata &t)
{
    d.space() << "taskId:" << t.taskId();
    return d;
}

McpProtocolRelatedTaskMetadata McpProtocolRelatedTaskMetadata::fromJson(const QJsonObject &obj)
{
    McpProtocolRelatedTaskMetadata task;
    task.setTaskId(obj["taskId"_L1].toString());
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
