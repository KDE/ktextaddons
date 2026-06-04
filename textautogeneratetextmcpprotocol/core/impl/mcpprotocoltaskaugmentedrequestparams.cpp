/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltaskaugmentedrequestparams.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolTaskAugmentedRequestParams::McpProtocolTaskAugmentedRequestParams() = default;

McpProtocolTaskAugmentedRequestParams::~McpProtocolTaskAugmentedRequestParams() = default;

bool McpProtocolTaskAugmentedRequestParams::operator==(const McpProtocolTaskAugmentedRequestParams &other) const = default;

bool McpProtocolTaskAugmentedRequestParams::Meta::operator==(const McpProtocolTaskAugmentedRequestParams::Meta &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolTaskAugmentedRequestParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "tasks:" << t.tasks();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolTaskAugmentedRequestParams::Meta &t)
{
    d.space() << "progressToken:" << t.progressToken();
    return d;
}

McpProtocolTaskAugmentedRequestParams::Meta McpProtocolTaskAugmentedRequestParams::Meta::fromJson(const QJsonObject &obj)
{
    McpProtocolTaskAugmentedRequestParams::Meta meta;
    if (obj.contains("progressToken"_L1)) {
        meta.setProgressToken(McpProtocolUtils::progressTokenFromJson(obj["progressToken"_L1]));
    }
    return meta;
}

QJsonObject McpProtocolTaskAugmentedRequestParams::Meta::toJson(const McpProtocolTaskAugmentedRequestParams::Meta &image)
{
    QJsonObject obj;
    if (image.progressToken().has_value()) {
        obj["progressToken"_L1] = McpProtocolUtils::progressTokenToJson(*image.progressToken());
    }
    return obj;
}

McpProtocolTaskAugmentedRequestParams McpProtocolTaskAugmentedRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolTaskAugmentedRequestParams prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolTaskAugmentedRequestParams::Meta::fromJson(obj["_meta"_L1].toObject()));
    }
    if (obj.contains("task"_L1) && obj["task"_L1].isObject()) {
        prompt.setTasks(McpProtocolTaskMetadata::fromJson(obj["task"_L1].toObject()));
    }

    return prompt;
}

QJsonObject McpProtocolTaskAugmentedRequestParams::toJson(const McpProtocolTaskAugmentedRequestParams &boolean)
{
    QJsonObject obj;

    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolTaskAugmentedRequestParams::Meta::toJson(*boolean.meta());
    }
    if (boolean.tasks().has_value()) {
        obj["task"_L1] = McpProtocolTaskMetadata::toJson(*boolean.tasks());
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

std::optional<McpProtocolTaskMetadata> McpProtocolTaskAugmentedRequestParams::tasks() const
{
    return mTasks;
}

void McpProtocolTaskAugmentedRequestParams::setTasks(std::optional<McpProtocolTaskMetadata> newTasks)
{
    mTasks = std::move(newTasks);
}

std::optional<McpProtocolUtils::ProgressToken> McpProtocolTaskAugmentedRequestParams::Meta::progressToken() const
{
    return mProgressToken;
}

void McpProtocolTaskAugmentedRequestParams::Meta::setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken)
{
    mProgressToken = std::move(newProgressToken);
}
