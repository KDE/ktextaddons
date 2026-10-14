/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltaskaugmentedrequestparams.h"
#include <QDebug>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolTaskAugmentedRequestParams::McpProtocolTaskAugmentedRequestParams() = default;

bool McpProtocolTaskAugmentedRequestParams::operator==(const McpProtocolTaskAugmentedRequestParams &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolTaskAugmentedRequestParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "task:" << t.task();
    return d;
}

McpProtocolTaskAugmentedRequestParams McpProtocolTaskAugmentedRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolTaskAugmentedRequestParams prompt;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        prompt.setMeta(McpProtocolTaskAugmentedRequestParams::Meta::fromJson(metaValue.toObject()));
    }
    if (const QJsonValue taskValue = obj.value("task"_L1); taskValue.isObject()) {
        prompt.setTask(McpProtocolTaskMetadata::fromJson(taskValue.toObject()));
    }

    return prompt;
}

QJsonObject McpProtocolTaskAugmentedRequestParams::toJson(const McpProtocolTaskAugmentedRequestParams &taskAugmentedRequestParams)
{
    QJsonObject obj;

    if (taskAugmentedRequestParams.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolTaskAugmentedRequestParams::Meta::toJson(*taskAugmentedRequestParams.meta());
    }
    if (taskAugmentedRequestParams.task().has_value()) {
        obj["task"_L1] = McpProtocolTaskMetadata::toJson(*taskAugmentedRequestParams.task());
    }
    return obj;
}

std::optional<McpProtocolTaskAugmentedRequestParams::Meta> McpProtocolTaskAugmentedRequestParams::meta() const
{
    return mMeta;
}

void McpProtocolTaskAugmentedRequestParams::setMeta(std::optional<Meta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<McpProtocolTaskMetadata> McpProtocolTaskAugmentedRequestParams::task() const
{
    return mTask;
}

void McpProtocolTaskAugmentedRequestParams::setTask(std::optional<McpProtocolTaskMetadata> newTask)
{
    mTask = std::move(newTask);
}
