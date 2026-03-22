/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcalltoolrequestparams.h"
#include "textautogeneratetextmcpprotocol_debug.h"
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
    return d;
}

McpProtocolCallToolRequestParams::Meta McpProtocolCallToolRequestParams::Meta::fromJson(const QJsonObject &obj)
{
    return {};
}

QJsonObject McpProtocolCallToolRequestParams::Meta::toJson(const McpProtocolCallToolRequestParams::Meta &image)
{
    QJsonObject obj;
#if 0
    if (image.progressToken().has_value()) {
        obj.insert("progressToken", McpProtocolUtils::toJson(*image.progressToken()));
    }
#endif
    return obj;
}

McpProtocolCallToolRequestParams McpProtocolCallToolRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolCallToolRequestParams prompt;
    // TODO
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
    mMeta = newMeta;
}

std::optional<McpProtocolUtils::ProgressToken> McpProtocolCallToolRequestParams::Meta::progressToken() const
{
    return mProgressToken;
}

void McpProtocolCallToolRequestParams::Meta::setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken)
{
    mProgressToken = std::move(newProgressToken);
}
