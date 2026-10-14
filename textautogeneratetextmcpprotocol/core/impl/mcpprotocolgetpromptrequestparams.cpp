/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolgetpromptrequestparams.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolGetPromptRequestParams::McpProtocolGetPromptRequestParams() = default;

bool McpProtocolGetPromptRequestParams::operator==(const McpProtocolGetPromptRequestParams &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolGetPromptRequestParams &t)
{
    d.space() << "name:" << t.name();
    d.space() << "meta:" << t.meta();
    d.space() << "arguments:" << t.arguments();
    return d;
}

bool McpProtocolGetPromptRequestParams::isValid() const
{
    return !mName.isEmpty();
}

McpProtocolGetPromptRequestParams McpProtocolGetPromptRequestParams::fromJson(const QJsonObject &obj)
{
    const QJsonValue nameValue = obj.value("name"_L1);
    if (!nameValue.isString()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolGetPromptRequestParams: missing required field 'name'";
        return {};
    }
    McpProtocolGetPromptRequestParams params;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        params.setMeta(McpProtocolGetPromptRequestParams::Meta::fromJson(metaValue.toObject()));
    }
    if (const QJsonValue argumentsValue = obj.value("arguments"_L1); argumentsValue.isObject()) {
        const QJsonObject mapObj_arguments = argumentsValue.toObject();
        QMap<QString, QString> map_arguments;
        for (auto it = mapObj_arguments.constBegin(); it != mapObj_arguments.constEnd(); ++it) {
            map_arguments.insert(it.key(), it.value().toString());
        }
        params.setArguments(std::move(map_arguments));
    }
    params.setName(nameValue.toString());
    return params;
}

QJsonObject McpProtocolGetPromptRequestParams::toJson(const McpProtocolGetPromptRequestParams &params)
{
    QJsonObject obj;
    obj["name"_L1] = params.name();

    if (params.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolGetPromptRequestParams::Meta::toJson(*params.meta());
    }
    if (params.arguments().has_value()) {
        QJsonObject map_arguments;
        const auto argumentsValues = *params.arguments();
        for (auto it = argumentsValues.constBegin(); it != argumentsValues.constEnd(); ++it) {
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
