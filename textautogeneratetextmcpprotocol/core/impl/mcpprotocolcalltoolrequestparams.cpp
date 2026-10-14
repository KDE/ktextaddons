/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcalltoolrequestparams.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolCallToolRequestParams::McpProtocolCallToolRequestParams() = default;

bool McpProtocolCallToolRequestParams::operator==(const McpProtocolCallToolRequestParams &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCallToolRequestParams &t)
{
    d.space() << "name:" << t.name();
    d.space() << "meta:" << t.meta();
    d.space() << "task:" << t.task();
    d.space() << "arguments:" << t.arguments();
    return d;
}

bool McpProtocolCallToolRequestParams::isValid() const
{
    return !mName.isEmpty();
}

McpProtocolCallToolRequestParams McpProtocolCallToolRequestParams::fromJson(const QJsonObject &obj)
{
    const QJsonValue nameValue = obj.value("name"_L1);
    if (!nameValue.isString()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolCallToolRequestParams: missing required field 'name'";
        return {};
    }
    McpProtocolCallToolRequestParams params;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        params.setMeta(McpProtocolCallToolRequestParams::Meta::fromJson(metaValue.toObject()));
    }
    if (const QJsonValue argumentsValue = obj.value("arguments"_L1); argumentsValue.isObject()) {
        const QJsonObject mapObj_arguments = argumentsValue.toObject();
        QMap<QString, QJsonValue> map_arguments;
        for (auto it = mapObj_arguments.constBegin(); it != mapObj_arguments.constEnd(); ++it) {
            map_arguments.insert(it.key(), it.value());
        }
        params.setArguments(std::move(map_arguments));
    }
    params.setName(nameValue.toString());
    if (const QJsonValue taskValue = obj.value("task"_L1); taskValue.isObject()) {
        params.setTask(McpProtocolTaskMetadata::fromJson(taskValue.toObject()));
    }
    return params;
}

QJsonObject McpProtocolCallToolRequestParams::toJson(const McpProtocolCallToolRequestParams &params)
{
    QJsonObject obj;
    obj["name"_L1] = params.name();

    if (params.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolCallToolRequestParams::Meta::toJson(*params.meta());
    }
    if (params.arguments().has_value()) {
        QJsonObject map_arguments;
        const auto argumentsValues = *params.arguments();
        for (auto it = argumentsValues.constBegin(); it != argumentsValues.constEnd(); ++it) {
            map_arguments.insert(it.key(), it.value());
        }
        obj["arguments"_L1] = map_arguments;
    }
    if (params.task().has_value()) {
        obj["task"_L1] = McpProtocolTaskMetadata::toJson(*params.task());
    }
    return obj;
}

std::optional<QMap<QString, QJsonValue>> McpProtocolCallToolRequestParams::arguments() const
{
    return mArguments;
}

void McpProtocolCallToolRequestParams::setArguments(std::optional<QMap<QString, QJsonValue>> newArguments)
{
    mArguments = std::move(newArguments);
}

QString McpProtocolCallToolRequestParams::name() const
{
    return mName;
}

void McpProtocolCallToolRequestParams::setName(const QString &newName)
{
    mName = newName;
}

std::optional<McpProtocolTaskMetadata> McpProtocolCallToolRequestParams::task() const
{
    return mTask;
}

void McpProtocolCallToolRequestParams::setTask(std::optional<McpProtocolTaskMetadata> newTask)
{
    mTask = std::move(newTask);
}

std::optional<McpProtocolCallToolRequestParams::Meta> McpProtocolCallToolRequestParams::meta() const
{
    return mMeta;
}

void McpProtocolCallToolRequestParams::setMeta(std::optional<Meta> newMeta)
{
    mMeta = std::move(newMeta);
}
