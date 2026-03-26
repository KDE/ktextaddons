/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcalltoolrequestparams.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolCallToolRequestParams::McpProtocolCallToolRequestParams() = default;

McpProtocolCallToolRequestParams::~McpProtocolCallToolRequestParams() = default;

bool McpProtocolCallToolRequestParams::operator==(const McpProtocolCallToolRequestParams &other) const = default;
bool McpProtocolCallToolRequestParams::Meta::operator==(const McpProtocolCallToolRequestParams::Meta &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolCallToolRequestParams &t)
{
    d.space() << "name:" << t.name();
    d.space() << "meta:" << t.meta();
    d.space() << "task:" << t.task();
    d.space() << "arguments:" << t.arguments();
    return d;
}

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolCallToolRequestParams::Meta &t)
{
    d.space() << "meta:" << t.progressToken();
    return d;
}

McpProtocolCallToolRequestParams::Meta McpProtocolCallToolRequestParams::Meta::fromJson(const QJsonObject &obj)
{
    McpProtocolCallToolRequestParams::Meta meta;
    if (obj.contains("progressToken"_L1)) {
        meta.setProgressToken(McpProtocolUtils::progressTokenFromJson(obj["progressToken"_L1].toObject()));
    }
    return meta;
}

QJsonObject McpProtocolCallToolRequestParams::Meta::toJson(const McpProtocolCallToolRequestParams::Meta &image)
{
    QJsonObject obj;
    if (image.progressToken().has_value()) {
        obj["progressToken"_L1] = McpProtocolUtils::progressTokenToJson(*image.progressToken());
    }
    return obj;
}

McpProtocolCallToolRequestParams McpProtocolCallToolRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolCallToolRequestParams prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolCallToolRequestParams::Meta::fromJson(obj["_meta"_L1].toObject()));
    }
    if (obj.contains("arguments"_L1) && obj["arguments"_L1].isObject()) {
        const QJsonObject mapObj_arguments = obj["arguments"_L1].toObject();
        QMap<QString, QJsonValue> map_arguments;
        for (auto it = mapObj_arguments.constBegin(); it != mapObj_arguments.constEnd(); ++it) {
            map_arguments.insert(it.key(), it.value());
        }
        prompt.setArguments(map_arguments);
    }
    prompt.setName(obj.value("name"_L1).toString());
    if (obj.contains("task"_L1) && obj["task"_L1].isObject()) {
        prompt.setTask(McpProtocolTaskMetadata::fromJson(obj["task"_L1].toObject()));
    }
    return prompt;
}

QJsonObject McpProtocolCallToolRequestParams::toJson(const McpProtocolCallToolRequestParams &boolean)
{
    QJsonObject obj;
    obj["name"_L1] = boolean.name();

    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolCallToolRequestParams::Meta::toJson(*boolean.meta());
    }
    if (boolean.arguments().has_value()) {
        QJsonObject map_arguments;
        for (auto it = boolean.arguments()->constBegin(); it != boolean.arguments()->constEnd(); ++it) {
            map_arguments.insert(it.key(), it.value());
        }
        obj["arguments"_L1] = map_arguments;
    }
    if (boolean.task().has_value()) {
        obj["task"_L1] = McpProtocolTaskMetadata::toJson(*boolean.task());
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

std::optional<McpProtocolUtils::ProgressToken> McpProtocolCallToolRequestParams::Meta::progressToken() const
{
    return mProgressToken;
}

void McpProtocolCallToolRequestParams::Meta::setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken)
{
    mProgressToken = std::move(newProgressToken);
}
