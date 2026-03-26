/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltoolexecution.h"
#include "textautogeneratetextmcpprotocol_debug.h"

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
    McpProtocolToolExecution result;
    if (obj.contains("taskSupport"_L1) && obj["taskSupport"_L1].isString()) {
        result.setTaskSupport(McpProtocolToolExecution::convertTaskSupportFromString(obj["taskSupport"_L1].toString()));
    }
    return result;
}

QJsonObject McpProtocolToolExecution::toJson(const McpProtocolToolExecution &execution)
{
    QJsonObject obj;
    if (execution.taskSupport().has_value()) {
        obj["taskSupport"_L1] = convertTaskSupportToString(*execution.taskSupport());
    }
    return obj;
}

McpProtocolToolExecution::TaskSupport McpProtocolToolExecution::convertTaskSupportFromString(const QString &str)
{
    if (str == "forbidden"_L1)
        return TaskSupport::Forbidden;
    if (str == "optional"_L1)
        return TaskSupport::Optional;
    if (str == "required"_L1)
        return TaskSupport::Required;
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Invalid task support " << str;
    return TaskSupport::Unknown;
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

std::optional<McpProtocolToolExecution::TaskSupport> McpProtocolToolExecution::taskSupport() const
{
    return mTaskSupport;
}

void McpProtocolToolExecution::setTaskSupport(std::optional<TaskSupport> newTaskSupport)
{
    mTaskSupport = newTaskSupport;
}

#include "moc_mcpprotocoltoolexecution.cpp"
