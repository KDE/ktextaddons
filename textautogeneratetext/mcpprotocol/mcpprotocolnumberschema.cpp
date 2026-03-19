/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolnumberschema.h"
#include <QDebug>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
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

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolNumberSchema &t)
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
    return prompt;
}

QJsonObject McpProtocolNumberSchema::toJson(const McpProtocolNumberSchema &boolean)
{
    QJsonObject obj;
    return obj;
}
