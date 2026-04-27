/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolgetpromptrequestparams.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolGetPromptRequestParams::McpProtocolGetPromptRequestParams() = default;

McpProtocolGetPromptRequestParams::~McpProtocolGetPromptRequestParams() = default;

bool McpProtocolGetPromptRequestParams::operator==(const McpProtocolGetPromptRequestParams &other) const = default;

bool McpProtocolGetPromptRequestParams::Meta::operator==(const McpProtocolGetPromptRequestParams::Meta &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolGetPromptRequestParams &t)
{
    d.space() << "name:" << t.name();
    d.space() << "meta:" << t.meta();
    d.space() << "arguments:" << t.arguments();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolGetPromptRequestParams::Meta &t)
{
    d.space() << "progressToken:" << t.progressToken();
    return d;
}

McpProtocolGetPromptRequestParams::Meta McpProtocolGetPromptRequestParams::Meta::fromJson(const QJsonObject &obj)
{
    McpProtocolGetPromptRequestParams::Meta meta;
    if (obj.contains("progressToken"_L1)) {
        meta.setProgressToken(McpProtocolUtils::progressTokenFromJson(obj["progressToken"_L1].toObject()));
    }
    return meta;
}

QJsonObject McpProtocolGetPromptRequestParams::Meta::toJson(const McpProtocolGetPromptRequestParams::Meta &image)
{
    QJsonObject obj;
    if (image.progressToken().has_value()) {
        obj["progressToken"_L1] = McpProtocolUtils::progressTokenToJson(*image.progressToken());
    }
    return obj;
}

McpProtocolGetPromptRequestParams McpProtocolGetPromptRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolGetPromptRequestParams prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolGetPromptRequestParams::Meta::fromJson(obj["_meta"_L1].toObject()));
    }
    if (obj.contains("arguments"_L1) && obj["arguments"_L1].isObject()) {
        const QJsonObject mapObj_arguments = obj["arguments"_L1].toObject();
        QMap<QString, QString> map_arguments;
        for (auto it = mapObj_arguments.constBegin(); it != mapObj_arguments.constEnd(); ++it) {
            map_arguments.insert(it.key(), it.value().toString());
        }
        prompt.setArguments(map_arguments);
    }
    prompt.setName(obj.value("name"_L1).toString());
    return prompt;
}

QJsonObject McpProtocolGetPromptRequestParams::toJson(const McpProtocolGetPromptRequestParams &boolean)
{
    QJsonObject obj;
    obj["name"_L1] = boolean.name();

    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolGetPromptRequestParams::Meta::toJson(*boolean.meta());
    }
    if (boolean.arguments().has_value()) {
        QJsonObject map_arguments;
        for (auto it = boolean.arguments()->constBegin(); it != boolean.arguments()->constEnd(); ++it) {
            map_arguments.insert(it.key(), it.value());
        }
        obj["arguments"_L1] = map_arguments;
    }
    return obj;
}

std::optional<QMap<QString, QString>> McpProtocolGetPromptRequestParams::arguments() const
{
    return mArguments;
}

void McpProtocolGetPromptRequestParams::setArguments(std::optional<QMap<QString, QString>> newArguments)
{
    mArguments = std::move(newArguments);
}

QString McpProtocolGetPromptRequestParams::name() const
{
    return mName;
}

void McpProtocolGetPromptRequestParams::setName(const QString &newName)
{
    mName = newName;
}

std::optional<McpProtocolGetPromptRequestParams::Meta> McpProtocolGetPromptRequestParams::meta() const
{
    return mMeta;
}

void McpProtocolGetPromptRequestParams::setMeta(std::optional<Meta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<McpProtocolUtils::ProgressToken> McpProtocolGetPromptRequestParams::Meta::progressToken() const
{
    return mProgressToken;
}

void McpProtocolGetPromptRequestParams::Meta::setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken)
{
    mProgressToken = std::move(newProgressToken);
}
