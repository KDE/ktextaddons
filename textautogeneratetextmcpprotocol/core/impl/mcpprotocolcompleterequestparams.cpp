/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcompleterequestparams.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonObject>
#include <type_traits>
#include <utility>
#include <variant>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolCompleteRequestParams::McpProtocolCompleteRequestParams() = default;

bool McpProtocolCompleteRequestParams::operator==(const McpProtocolCompleteRequestParams &other) const = default;
bool McpProtocolCompleteRequestParams::Meta::operator==(const McpProtocolCompleteRequestParams::Meta &other) const = default;

std::optional<QMap<QString, QString>> McpProtocolCompleteRequestParams::Context::arguments() const
{
    return mArguments;
}

void McpProtocolCompleteRequestParams::Context::setArguments(std::optional<QMap<QString, QString>> newArguments)
{
    mArguments = std::move(newArguments);
}

McpProtocolCompleteRequestParams::Context McpProtocolCompleteRequestParams::Context::fromJson(const QJsonObject &obj)
{
    McpProtocolCompleteRequestParams::Context context;
    if (const QJsonValue argumentsValue = obj.value("arguments"_L1); argumentsValue.isObject()) {
        const QJsonObject mapObj_arguments = argumentsValue.toObject();
        QMap<QString, QString> map_arguments;
        for (auto it = mapObj_arguments.constBegin(); it != mapObj_arguments.constEnd(); ++it) {
            map_arguments.insert(it.key(), it.value().toString());
        }
        context.setArguments(std::move(map_arguments));
    }
    return context;
}

QJsonObject McpProtocolCompleteRequestParams::Context::toJson(const Context &context)
{
    QJsonObject obj;
    if (context.arguments().has_value()) {
        const auto arguments = *context.arguments();
        QJsonObject map_arguments;
        for (auto it = arguments.constBegin(); it != arguments.constEnd(); ++it) {
            map_arguments.insert(it.key(), QJsonValue(it.value()));
        }
        obj.insert("arguments"_L1, map_arguments);
    }
    return obj;
}

bool McpProtocolCompleteRequestParams::Context::operator==(const McpProtocolCompleteRequestParams::Context &other) const = default;

QString McpProtocolCompleteRequestParams::Argument::value() const
{
    return mValue;
}

void McpProtocolCompleteRequestParams::Argument::setValue(const QString &newValue)
{
    mValue = newValue;
}

QString McpProtocolCompleteRequestParams::Argument::name() const
{
    return mName;
}

void McpProtocolCompleteRequestParams::Argument::setName(const QString &newName)
{
    mName = newName;
}

bool McpProtocolCompleteRequestParams::Argument::isValid() const
{
    // value can be empty (nothing typed yet)
    return !mName.isEmpty();
}

McpProtocolCompleteRequestParams::Argument McpProtocolCompleteRequestParams::Argument::fromJson(const QJsonObject &obj)
{
    const QJsonValue nameValue = obj.value("name"_L1);
    if (!nameValue.isString()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolCompleteRequestParams::Argument: missing required field 'name'";
        return {};
    }
    const QJsonValue valueValue = obj.value("value"_L1);
    if (!valueValue.isString()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolCompleteRequestParams::Argument: missing required field 'value'";
        return {};
    }
    McpProtocolCompleteRequestParams::Argument argument;
    argument.setName(nameValue.toString());
    argument.setValue(valueValue.toString());
    return argument;
}

QJsonObject McpProtocolCompleteRequestParams::Argument::toJson(const Argument &argument)
{
    QJsonObject obj;
    obj["name"_L1] = argument.name();
    obj["value"_L1] = argument.value();
    return obj;
}

bool McpProtocolCompleteRequestParams::Argument::operator==(const McpProtocolCompleteRequestParams::Argument &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCompleteRequestParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "argument:" << t.argument();
    d.space() << "context:" << t.context();
    d.space() << "ref:" << McpProtocolUtils::getCompleteRequestParamsRef(t.ref());

    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCompleteRequestParams::Meta &t)
{
    d.space() << "progressToken:" << t.progressToken();
    d.space() << "additionalProperties:" << t.additionalProperties();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCompleteRequestParams::Argument &t)
{
    d.space() << "value:" << t.value();
    d.space() << "name:" << t.name();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCompleteRequestParams::Context &t)
{
    d.space() << "arguments:" << t.arguments();
    return d;
}

McpProtocolCompleteRequestParams::Meta McpProtocolCompleteRequestParams::Meta::fromJson(const QJsonObject &obj)
{
    McpProtocolCompleteRequestParams::Meta meta;
    if (obj.contains("progressToken"_L1)) {
        meta.setProgressToken(McpProtocolUtils::progressTokenFromJson(obj["progressToken"_L1]));
    }
    QJsonObject additionalProperties = obj;
    additionalProperties.remove("progressToken"_L1);
    meta.setAdditionalProperties(additionalProperties);
    return meta;
}

QJsonObject McpProtocolCompleteRequestParams::Meta::toJson(const McpProtocolCompleteRequestParams::Meta &meta)
{
    QJsonObject obj = meta.additionalProperties();
    if (meta.progressToken().has_value()) {
        obj["progressToken"_L1] = McpProtocolUtils::progressTokenToJson(*meta.progressToken());
    }
    return obj;
}

static bool isRefValid(const McpProtocolUtils::CompleteRequestParamsRef &ref)
{
    // A rejected reference is default-constructed
    return std::visit(
        [](const auto &r) -> bool {
            using T = std::decay_t<decltype(r)>;
            return !(r == T());
        },
        ref);
}

bool McpProtocolCompleteRequestParams::isValid() const
{
    return mArgument.isValid() && isRefValid(mRef);
}

McpProtocolCompleteRequestParams McpProtocolCompleteRequestParams::fromJson(const QJsonObject &obj)
{
    const QJsonValue argumentValue = obj.value("argument"_L1);
    if (!argumentValue.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolCompleteRequestParams: missing required field 'argument'";
        return {};
    }
    const McpProtocolCompleteRequestParams::Argument argument = McpProtocolCompleteRequestParams::Argument::fromJson(argumentValue.toObject());
    if (!argument.isValid()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolCompleteRequestParams: invalid field 'argument'";
        return {};
    }
    const QJsonValue refValue = obj.value("ref"_L1);
    if (!refValue.isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolCompleteRequestParams: missing required field 'ref'";
        return {};
    }
    const McpProtocolUtils::CompleteRequestParamsRef ref = McpProtocolUtils::completeRequestParamsRefFromJson(refValue);
    if (!isRefValid(ref)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolCompleteRequestParams: invalid field 'ref'";
        return {};
    }
    McpProtocolCompleteRequestParams params;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        params.setMeta(McpProtocolCompleteRequestParams::Meta::fromJson(metaValue.toObject()));
    }
    params.setArgument(argument);
    if (const QJsonValue contextValue = obj.value("context"_L1); contextValue.isObject()) {
        params.setContext(McpProtocolCompleteRequestParams::Context::fromJson(contextValue.toObject()));
    }
    params.setRef(ref);
    return params;
}

QJsonObject McpProtocolCompleteRequestParams::toJson(const McpProtocolCompleteRequestParams &params)
{
    QJsonObject obj;
    if (params.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolCompleteRequestParams::Meta::toJson(*params.meta());
    }
    obj["argument"_L1] = Argument::toJson(params.argument());
    obj["ref"_L1] = McpProtocolUtils::completeRequestParamsRefToJson(params.ref());
    if (params.context().has_value()) {
        obj.insert("context"_L1, Context::toJson(*params.context()));
    }
    return obj;
}

std::optional<McpProtocolCompleteRequestParams::Meta> McpProtocolCompleteRequestParams::meta() const
{
    return mMeta;
}

void McpProtocolCompleteRequestParams::setMeta(std::optional<Meta> newMeta)
{
    mMeta = std::move(newMeta);
}

McpProtocolCompleteRequestParams::Argument McpProtocolCompleteRequestParams::argument() const
{
    return mArgument;
}

void McpProtocolCompleteRequestParams::setArgument(Argument newArgument)
{
    mArgument = std::move(newArgument);
}

std::optional<McpProtocolCompleteRequestParams::Context> McpProtocolCompleteRequestParams::context() const
{
    return mContext;
}

void McpProtocolCompleteRequestParams::setContext(std::optional<Context> newContext)
{
    mContext = std::move(newContext);
}

McpProtocolUtils::CompleteRequestParamsRef McpProtocolCompleteRequestParams::ref() const
{
    return mRef;
}

void McpProtocolCompleteRequestParams::setRef(McpProtocolUtils::CompleteRequestParamsRef newRef)
{
    mRef = std::move(newRef);
}

std::optional<McpProtocolUtils::ProgressToken> McpProtocolCompleteRequestParams::Meta::progressToken() const
{
    return mProgressToken;
}

void McpProtocolCompleteRequestParams::Meta::setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken)
{
    mProgressToken = std::move(newProgressToken);
}

QJsonObject McpProtocolCompleteRequestParams::Meta::additionalProperties() const
{
    return mAdditionalProperties;
}

void McpProtocolCompleteRequestParams::Meta::setAdditionalProperties(const QJsonObject &newAdditionalProperties)
{
    mAdditionalProperties = newAdditionalProperties;
}
