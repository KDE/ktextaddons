/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolelicitrequestformparams.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolElicitRequestFormParams::McpProtocolElicitRequestFormParams() = default;
McpProtocolElicitRequestFormParams::~McpProtocolElicitRequestFormParams() = default;

bool McpProtocolElicitRequestFormParams::operator==(const McpProtocolElicitRequestFormParams &other) const = default;

bool McpProtocolElicitRequestFormParams::Meta::operator==(const McpProtocolElicitRequestFormParams::Meta &other) const = default;

bool McpProtocolElicitRequestFormParams::RequestedSchema::operator==(const McpProtocolElicitRequestFormParams::RequestedSchema &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestFormParams &t)
{
    d.space() << "message:" << t.message();
    d.space() << "task:" << t.task();
    d.space() << "requestedSchema:" << McpProtocolElicitRequestFormParams::RequestedSchema::toJson(t.requestedSchema());
    return d;
}

McpProtocolElicitRequestFormParams::Meta McpProtocolElicitRequestFormParams::Meta::fromJson(const QJsonObject &obj)
{
    McpProtocolElicitRequestFormParams::Meta meta;
    if (obj.contains("progressToken"_L1)) {
        meta.setProgressToken(McpProtocolUtils::progressTokenFromJson(obj["progressToken"_L1]));
    }
    return meta;
}

QJsonObject McpProtocolElicitRequestFormParams::Meta::toJson(const McpProtocolElicitRequestFormParams::Meta &image)
{
    QJsonObject obj;
    if (image.progressToken().has_value()) {
        obj["progressToken"_L1] = McpProtocolUtils::progressTokenToJson(*image.progressToken());
    }
    return obj;
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
    if (!obj.contains("properties"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: properties";
        return {};
    }
    McpProtocolElicitRequestFormParams::RequestedSchema requestedSchema;
    if (obj.contains("$schema"_L1)) {
        requestedSchema.setDollarschema(obj.value("$schema"_L1).toString());
    }
    const QJsonObject mapObj_properties = obj["properties"_L1].toObject();
    QMap<QString, McpProtocolUtils::PrimitiveSchemaDefinition> map_properties;
    for (auto it = mapObj_properties.constBegin(); it != mapObj_properties.constEnd(); ++it) {
        map_properties.insert(it.key(), McpProtocolUtils::primitiveSchemaDefinitionFromJson(it.value()));
    }
    requestedSchema.setProperties(map_properties);
    if (obj.contains("required"_L1) && obj["required"_L1].isArray()) {
        const QJsonArray arr = obj["required"_L1].toArray();
        QStringList list_required;
        list_required.reserve(arr.count());
        for (const QJsonValue &v : arr) {
            list_required.append(v.toString());
        }
        requestedSchema.setRequired(list_required);
    }
    return requestedSchema;
}

QJsonObject McpProtocolElicitRequestFormParams::RequestedSchema::toJson(const McpProtocolElicitRequestFormParams::RequestedSchema &image)
{
    QJsonObject obj;
    obj["type"_L1] = u"object"_s;
    if (image.dollarschema().has_value()) {
        obj["$schema"_L1] = *image.dollarschema();
    }
    QJsonObject map_properties;
    const auto properties = image.properties();
    for (auto it = properties.constBegin(); it != properties.constEnd(); ++it) {
        map_properties.insert(it.key(), McpProtocolUtils::primitiveSchemaDefinitionToJson(it.value()));
    }
    obj["properties"_L1] = map_properties;
    if (image.required().has_value()) {
        QJsonArray arr_required;
        const auto required = *image.required();
        for (const auto &v : required) {
            arr_required.append(v);
        }
        obj["required"_L1] = arr_required;
    }
    return obj;
}

QByteArray McpProtocolElicitRequestFormParams::mode()
{
    return "form"_ba;
}

McpProtocolElicitRequestFormParams McpProtocolElicitRequestFormParams::fromJson(const QJsonObject &obj)
{
    McpProtocolElicitRequestFormParams params;
    if (obj.value("mode"_L1).toString() != QString::fromLatin1(McpProtocolElicitRequestFormParams::mode())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolElicitRequestFormParams: mode is not correct " << obj.value("mode"_L1).toString();
        return {};
    }
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        params.setMeta(McpProtocolElicitRequestFormParams::Meta::fromJson(obj["_meta"_L1].toObject()));
    }
    params.setMessage(obj.value("message"_L1).toString());
    if (obj.contains("requestedSchema"_L1) && obj["requestedSchema"_L1].isObject()) {
        params.setRequestedSchema(McpProtocolElicitRequestFormParams::RequestedSchema::fromJson(obj["requestedSchema"_L1].toObject()));
    }
    if (obj.contains("task"_L1) && obj["task"_L1].isObject()) {
        params.setTask(McpProtocolTaskMetadata::fromJson(obj["task"_L1].toObject()));
    }
    return params;
}

QJsonObject McpProtocolElicitRequestFormParams::toJson(const McpProtocolElicitRequestFormParams &image)
{
    QJsonObject obj;
    obj["mode"_L1] = QString::fromLatin1(McpProtocolElicitRequestFormParams::mode());
    if (image.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolElicitRequestFormParams::Meta::toJson(*image.meta());
    }
    obj["message"_L1] = image.message();
    obj["requestedSchema"_L1] = McpProtocolElicitRequestFormParams::RequestedSchema::toJson(image.requestedSchema());
    if (image.task().has_value()) {
        obj["task"_L1] = McpProtocolTaskMetadata::toJson(*image.task());
    }
    return obj;
}

std::optional<McpProtocolElicitRequestFormParams::Meta> McpProtocolElicitRequestFormParams::meta() const
{
    return mMeta;
}

void McpProtocolElicitRequestFormParams::setMeta(std::optional<Meta> newMeta)
{
    mMeta = std::move(newMeta);
}

McpProtocolElicitRequestFormParams::RequestedSchema McpProtocolElicitRequestFormParams::requestedSchema() const
{
    return mRequestedSchema;
}

void McpProtocolElicitRequestFormParams::setRequestedSchema(const RequestedSchema &newRequestedSchema)
{
    mRequestedSchema = newRequestedSchema;
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
QMap<QString, McpProtocolUtils::PrimitiveSchemaDefinition> McpProtocolElicitRequestFormParams::RequestedSchema::properties() const
{
    return mProperties;
}

void McpProtocolElicitRequestFormParams::RequestedSchema::setProperties(const QMap<QString, McpProtocolUtils::PrimitiveSchemaDefinition> &newProperties)
{
    mProperties = newProperties;
}
