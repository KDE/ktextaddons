/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolnumberschema.h"
#include <QDebug>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolNumberSchema::McpProtocolNumberSchema() = default;

McpProtocolNumberSchema::~McpProtocolNumberSchema() = default;

bool McpProtocolNumberSchema::operator==(const McpProtocolNumberSchema &other) const = default;

std::optional<int> McpProtocolNumberSchema::defaultValue() const
{
    return mDefaultValue;
}

void McpProtocolNumberSchema::setDefaultValue(std::optional<int> newDefaultValue)
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

std::optional<int> McpProtocolNumberSchema::maximum() const
{
    return mMaximum;
}

void McpProtocolNumberSchema::setMaximum(std::optional<int> newMaximum)
{
    mMaximum = newMaximum;
}

std::optional<int> McpProtocolNumberSchema::minimum() const
{
    return mMinimum;
}

void McpProtocolNumberSchema::setMinimum(std::optional<int> newMinimum)
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

QString McpProtocolNumberSchema::convertNumberSchemaTypeToString(McpProtocolNumberSchema::Type level)
{
    switch (level) {
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
    } else {
        return {};
    }
}

McpProtocolNumberSchema McpProtocolNumberSchema::fromJson(const QJsonObject &obj)
{
    McpProtocolNumberSchema prompt;
    if (obj.contains("default"_L1)) {
        prompt.setDefaultValue(obj.value("default"_L1).toInt());
    }
    if (obj.contains("description"_L1)) {
        prompt.setDescription(obj.value("description"_L1).toString());
    }
    if (obj.contains("maximum"_L1)) {
        prompt.setMaximum(obj.value("maximum"_L1).toInt());
    }
    if (obj.contains("minimum"_L1)) {
        prompt.setMinimum(obj.value("minimum"_L1).toInt());
    }
    if (obj.contains("title"_L1)) {
        prompt.setTitle(obj.value("title"_L1).toString());
    }
    if (obj.contains("type"_L1) && obj["type"_L1].isString()) {
        prompt.setType(convertNumberSchemaTypeFromString(obj["type"_L1].toString()));
    }
    return prompt;
}

QJsonObject McpProtocolNumberSchema::toJson(const McpProtocolNumberSchema &boolean)
{
    QJsonObject obj;
    obj["type"_L1] = convertNumberSchemaTypeToString(boolean.type());
    if (boolean.defaultValue().has_value()) {
        obj.insert("default"_L1, *boolean.defaultValue());
    }
    if (boolean.description().has_value()) {
        obj.insert("description"_L1, *boolean.description());
    }
    if (boolean.maximum().has_value()) {
        obj.insert("maximum"_L1, *boolean.maximum());
    }
    if (boolean.minimum().has_value()) {
        obj.insert("minimum"_L1, *boolean.minimum());
    }
    if (boolean.title().has_value()) {
        obj.insert("title"_L1, *boolean.title());
    }
    return obj;
}
