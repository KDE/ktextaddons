/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltoolexecution.h"
#include <QDebug>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolToolExecution::McpProtocolToolExecution() = default;

McpProtocolToolExecution::~McpProtocolToolExecution() = default;

bool McpProtocolToolExecution::operator==(const McpProtocolToolExecution &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolToolExecution &t)
{
    d.space() << "taskSupport:" << t.taskSupport();
    return d;
}

McpProtocolToolExecution McpProtocolToolExecution::fromJson(const QJsonObject &obj)
{
    return {};
}

QJsonObject McpProtocolToolExecution::toJson(const McpProtocolToolExecution &execution)
{
    QJsonObject obj;
    if (execution.taskSupport() != McpProtocolToolExecution::TaskSupport::Unknown) {
        obj["taskSupport"_L1] = convertTaskSupportToString(execution.taskSupport());
    }
    return obj;
}

McpProtocolToolExecution::TaskSupport McpProtocolToolExecution::taskSupport() const
{
    return mTaskSupport;
}

void McpProtocolToolExecution::setTaskSupport(TaskSupport newTaskSupport)
{
    mTaskSupport = newTaskSupport;
}

QString McpProtocolToolExecution::convertTaskSupportToString(McpProtocolToolExecution::TaskSupport mode)
{
    switch (mode) {
    case TaskSupport::Forbidden:
        return u"forbidden"_s;
    case TaskSupport::Optional:
        return u"optional"_s;
    case TaskSupport::Required:
        return u"required"_s;
    case TaskSupport::Unknown:
        return {};
    }
    return {};
}

#include "moc_mcpprotocoltoolexecution.cpp"
