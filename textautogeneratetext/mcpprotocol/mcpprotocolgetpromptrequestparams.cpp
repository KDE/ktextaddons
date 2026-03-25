/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolgetpromptrequestparams.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolGetPromptRequestParams::McpProtocolGetPromptRequestParams() = default;

McpProtocolGetPromptRequestParams::~McpProtocolGetPromptRequestParams() = default;

bool McpProtocolGetPromptRequestParams::operator==(const McpProtocolGetPromptRequestParams &other) const = default;
bool McpProtocolGetPromptRequestParams::Meta::operator==(const McpProtocolGetPromptRequestParams::Meta &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolGetPromptRequestParams &t)
{
    d.space() << "name:" << t.name();
    // TODO d.space() << "meta:" << t.meta();
    d.space() << "arguments:" << t.arguments();
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
    // TODO
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

std::optional<QMap<QString, QJsonValue>> McpProtocolGetPromptRequestParams::arguments() const
{
    return mArguments;
}

void McpProtocolGetPromptRequestParams::setArguments(std::optional<QMap<QString, QJsonValue>> newArguments)
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
