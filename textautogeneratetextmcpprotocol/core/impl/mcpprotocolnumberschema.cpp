/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolnumberschema.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolNumberSchema::McpProtocolNumberSchema() = default;

bool McpProtocolNumberSchema::operator==(const McpProtocolNumberSchema &other) const = default;

std::optional<double> McpProtocolNumberSchema::defaultValue() const
{
    return mDefaultValue;
}

void McpProtocolNumberSchema::setDefaultValue(std::optional<double> newDefaultValue)
{
    mDefaultValue = newDefaultValue;
}

std::optional<QString> McpProtocolNumberSchema::description() const
{
    return mDescription;
}

void McpProtocolNumberSchema::setDescription(std::optional<QString> newDescription)
{
    mDescription = std::move(newDescription);
}

std::optional<double> McpProtocolNumberSchema::maximum() const
{
    return mMaximum;
}

void McpProtocolNumberSchema::setMaximum(std::optional<double> newMaximum)
{
    mMaximum = newMaximum;
}

std::optional<double> McpProtocolNumberSchema::minimum() const
{
    return mMinimum;
}

void McpProtocolNumberSchema::setMinimum(std::optional<double> newMinimum)
{
    mMinimum = newMinimum;
}

std::optional<QString> McpProtocolNumberSchema::title() const
{
    return mTitle;
}

void McpProtocolNumberSchema::setTitle(std::optional<QString> newTitle)
{
    mTitle = std::move(newTitle);
}

McpProtocolNumberSchema::Type McpProtocolNumberSchema::type() const
{
    return mType;
}

void McpProtocolNumberSchema::setType(Type newType)
{
    mType = newType;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolNumberSchema &t)
{
    d.space() << "defaultValue:" << t.defaultValue();
    d.space() << "description:" << t.description();
    d.space() << "maximum:" << t.maximum();
    d.space() << "minimum:" << t.minimum();
    d.space() << "title:" << t.title();
    d.space() << "type:" << McpProtocolNumberSchema::convertNumberSchemaTypeToString(t.type());

    return d;
}

QString McpProtocolNumberSchema::convertNumberSchemaTypeToString(McpProtocolNumberSchema::Type type)
{
    switch (type) {
    case McpProtocolNumberSchema::Type::Integer:
        return u"integer"_s;
    case McpProtocolNumberSchema::Type::Number:
        return u"number"_s;
    case McpProtocolNumberSchema::Type::Unknown:
        return {};
    }
    return {};
}

McpProtocolNumberSchema::Type McpProtocolNumberSchema::convertNumberSchemaTypeFromString(const QString &str)
{
    if (str == "integer"_L1) {
        return McpProtocolNumberSchema::Type::Integer;
    } else if (str == "number"_L1) {
        return McpProtocolNumberSchema::Type::Number;
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid NumberSchema type: " << str;
    return McpProtocolNumberSchema::Type::Unknown;
}

McpProtocolNumberSchema McpProtocolNumberSchema::fromJson(const QJsonObject &obj)
{
    McpProtocolNumberSchema schema;
    // "type" is required: "number" or "integer"
    if (convertNumberSchemaTypeFromString(obj.value("type"_L1).toString()) == Type::Unknown) {
        return {};
    }
    if (const QJsonValue defaultValue = obj.value("default"_L1); defaultValue.isDouble()) {
        schema.setDefaultValue(defaultValue.toDouble());
    }
    if (obj.contains("description"_L1)) {
        schema.setDescription(obj.value("description"_L1).toString());
    }
    if (const QJsonValue maximumValue = obj.value("maximum"_L1); maximumValue.isDouble()) {
        schema.setMaximum(maximumValue.toDouble());
    }
    if (const QJsonValue minimumValue = obj.value("minimum"_L1); minimumValue.isDouble()) {
        schema.setMinimum(minimumValue.toDouble());
    }
    if (obj.contains("title"_L1)) {
        schema.setTitle(obj.value("title"_L1).toString());
    }
    if (const QJsonValue typeValue = obj.value("type"_L1); typeValue.isString()) {
        schema.setType(convertNumberSchemaTypeFromString(typeValue.toString()));
    }
    return schema;
}

QJsonObject McpProtocolNumberSchema::toJson(const McpProtocolNumberSchema &schema)
{
    QJsonObject obj;
    if (schema.type() != Type::Unknown) {
        obj["type"_L1] = convertNumberSchemaTypeToString(schema.type());
    }
    if (schema.defaultValue().has_value()) {
        obj.insert("default"_L1, *schema.defaultValue());
    }
    if (schema.description().has_value()) {
        obj.insert("description"_L1, *schema.description());
    }
    if (schema.maximum().has_value()) {
        obj.insert("maximum"_L1, *schema.maximum());
    }
    if (schema.minimum().has_value()) {
        obj.insert("minimum"_L1, *schema.minimum());
    }
    if (schema.title().has_value()) {
        obj.insert("title"_L1, *schema.title());
    }
    return obj;
}
