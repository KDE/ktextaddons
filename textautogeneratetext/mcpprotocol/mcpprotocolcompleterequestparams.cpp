/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcompleterequestparams.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolCompleteRequestParams::McpProtocolCompleteRequestParams() = default;

McpProtocolCompleteRequestParams::~McpProtocolCompleteRequestParams() = default;

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
    // TODO
    return context;
}

QJsonObject McpProtocolCompleteRequestParams::Context::toJson(const Context &image)
{
    QJsonObject obj;
    // TODO
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

McpProtocolCompleteRequestParams::Argument McpProtocolCompleteRequestParams::Argument::fromJson(const QJsonObject &obj)
{
    McpProtocolCompleteRequestParams::Argument argument;
    // TODO
    return argument;
}

QJsonObject McpProtocolCompleteRequestParams::Argument::toJson(const Argument &image)
{
    QJsonObject obj;
    // TODO
    return obj;
}

bool McpProtocolCompleteRequestParams::Argument::operator==(const McpProtocolCompleteRequestParams::Argument &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolCompleteRequestParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "argument:" << t.argument();
    d.space() << "context:" << t.context();
    // TODO d.space() << "ref:" << t.ref();

    return d;
}

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolCompleteRequestParams::Meta &t)
{
    d.space() << "progressToken" << t.progressToken();
    return d;
}

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolCompleteRequestParams::Argument &t)
{
    d.space() << "value" << t.value();
    d.space() << "name" << t.name();
    return d;
}

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolCompleteRequestParams::Context &t)
{
    d.space() << "arguments" << t.arguments();
    return d;
}

McpProtocolCompleteRequestParams::Meta McpProtocolCompleteRequestParams::Meta::fromJson(const QJsonObject &obj)
{
    McpProtocolCompleteRequestParams::Meta meta;
    if (obj.contains("progressToken"_L1)) {
        meta.setProgressToken(McpProtocolUtils::progressTokenFromJson(obj["progressToken"_L1].toObject()));
    }
    return meta;
}

QJsonObject McpProtocolCompleteRequestParams::Meta::toJson(const McpProtocolCompleteRequestParams::Meta &image)
{
    QJsonObject obj;
    if (image.progressToken().has_value()) {
        obj["progressToken"_L1] = McpProtocolUtils::progressTokenToJson(*image.progressToken());
    }
    return obj;
}

McpProtocolCompleteRequestParams McpProtocolCompleteRequestParams::fromJson(const QJsonObject &obj)
{
    McpProtocolCompleteRequestParams prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolCompleteRequestParams::Meta::fromJson(obj["_meta"_L1].toObject()));
    }
    if (obj.contains("argument"_L1) && obj["argument"_L1].isObject()) {
        prompt.setArgument(McpProtocolCompleteRequestParams::Argument::fromJson(obj["argument"_L1].toObject()));
    }
    if (obj.contains("context"_L1) && obj["context"_L1].isObject()) {
        prompt.setContext(McpProtocolCompleteRequestParams::Context::fromJson(obj["context"_L1].toObject()));
    }
    // REF
    // TODO
    return prompt;
}

QJsonObject McpProtocolCompleteRequestParams::toJson(const McpProtocolCompleteRequestParams &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolCompleteRequestParams::Meta::toJson(*boolean.meta());
    }
    obj["argument"_L1] = Argument::toJson(boolean.argument());
    // TODO obj["ref"_L1] = toJsonValue(boolean.ref());
    if (boolean.context().has_value()) {
        obj.insert("context"_L1, Context::toJson(*boolean.context()));
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

void McpProtocolCompleteRequestParams::setArgument(const Argument &newArgument)
{
    mArgument = newArgument;
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

void McpProtocolCompleteRequestParams::setRef(const McpProtocolUtils::CompleteRequestParamsRef &newRef)
{
    mRef = newRef;
}

std::optional<McpProtocolUtils::ProgressToken> McpProtocolCompleteRequestParams::Meta::progressToken() const
{
    return mProgressToken;
}

void McpProtocolCompleteRequestParams::Meta::setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken)
{
    mProgressToken = std::move(newProgressToken);
}
