/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolelicitrequestformparams.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolElicitRequestFormParams::McpProtocolElicitRequestFormParams() = default;
McpProtocolElicitRequestFormParams::~McpProtocolElicitRequestFormParams() = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestFormParams &t)
{
    // TODO
    return d;
}

std::optional<McpProtocolUtils::ProgressToken> McpProtocolElicitRequestFormParams::Meta::progressToken() const
{
    return mProgressToken;
}

void McpProtocolElicitRequestFormParams::Meta::setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken)
{
    mProgressToken = std::move(newProgressToken);
}

McpProtocolElicitRequestFormParams::RequestedSchema McpProtocolElicitRequestFormParams::RequestedSchema::fromJson(const QJsonObject &obj)
{
    // TODO
    return {};
}

QJsonObject McpProtocolElicitRequestFormParams::RequestedSchema::toJson(const McpProtocolElicitRequestFormParams::RequestedSchema &image)
{
    QJsonObject obj;
#if 0
    obj["type"_L1] = u"object"_s;
    if (image.dollarschema().has_value()) {
        obj["$schema"_L1] = *image.dollarschema();
    }
    QJsonObject map_properties;
#if 0 // TODO
    for (auto it = image.properties().constBegin(); it != image.properties().constEnd(); ++it) {
        map_properties.insert(it.key(), toJsonValue(it.value()));
    }
#endif
    obj["properties"_L1] =  map_properties;
    if (image.required().has_value()) {
        QJsonArray arr_required;
        const auto required = *image.required();
        for (const auto &v : required)  {
            arr_required.append(v);
        }
        obj["required"_L1] =  arr_required;
    }
#endif
    return obj;
}

McpProtocolElicitRequestFormParams McpProtocolElicitRequestFormParams::fromJson(const QJsonObject &obj)
{
    // TODO
    return {};
}

QJsonObject McpProtocolElicitRequestFormParams::toJson(const McpProtocolElicitRequestFormParams &image)
{
    // TODO
    return {};
}

QString McpProtocolElicitRequestFormParams::message() const
{
    return mMessage;
}

void McpProtocolElicitRequestFormParams::setMessage(const QString &newMessage)
{
    mMessage = newMessage;
}

std::optional<McpProtocolTaskMetadata> McpProtocolElicitRequestFormParams::task() const
{
    return mTask;
}

void McpProtocolElicitRequestFormParams::setTask(std::optional<McpProtocolTaskMetadata> newTask)
{
    mTask = std::move(newTask);
}

std::optional<QString> McpProtocolElicitRequestFormParams::RequestedSchema::dollarschema() const
{
    return mDollarschema;
}

void McpProtocolElicitRequestFormParams::RequestedSchema::setDollarschema(std::optional<QString> newDollarschema)
{
    mDollarschema = newDollarschema;
}

std::optional<QStringList> McpProtocolElicitRequestFormParams::RequestedSchema::required() const
{
    return mRequired;
}

void McpProtocolElicitRequestFormParams::RequestedSchema::setRequired(std::optional<QStringList> newRequired)
{
    mRequired = newRequired;
}
// TODO
#if 0
QMap<QString, McpProtocolUtils::PrimitiveSchemaDefinition> McpProtocolElicitRequestFormParams::RequestedSchema::properties() const
{
    return mProperties;
}

void McpProtocolElicitRequestFormParams::RequestedSchema::setProperties(const QMap<QString, McpProtocolUtils::PrimitiveSchemaDefinition> &newProperties)
{
    mProperties = newProperties;
}
#endif
