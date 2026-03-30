/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocollegacytitledenumschema.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolLegacyTitledEnumSchema::McpProtocolLegacyTitledEnumSchema() = default;

McpProtocolLegacyTitledEnumSchema::~McpProtocolLegacyTitledEnumSchema() = default;

bool McpProtocolLegacyTitledEnumSchema::operator==(const McpProtocolLegacyTitledEnumSchema &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolLegacyTitledEnumSchema &t)
{
    d.space() << "defaultValue:" << t.defaultValue();
    d.space() << "description:" << t.description();
    d.space() << "enums:" << t.enums();
    d.space() << "enumNames:" << t.enumNames();
    d.space() << "title:" << t.title();
    return d;
}

QByteArray McpProtocolLegacyTitledEnumSchema::type()
{
    return QByteArrayLiteral("string");
}

McpProtocolLegacyTitledEnumSchema McpProtocolLegacyTitledEnumSchema::fromJson(const QJsonObject &obj)
{
    McpProtocolLegacyTitledEnumSchema prompt;

    // TODO
    return prompt;
}

QJsonObject McpProtocolLegacyTitledEnumSchema::toJson(const McpProtocolLegacyTitledEnumSchema &boolean)
{
    QJsonObject obj;
    obj["type"_L1] = QString::fromLatin1(type());
    if (boolean.defaultValue().has_value()) {
        obj.insert("default"_L1, *boolean.defaultValue());
    }
    if (boolean.description().has_value()) {
        obj.insert("description"_L1, *boolean.description());
    }
    QJsonArray arr_enum_;
    for (const auto &v : boolean.enums()) {
        arr_enum_.append(v);
    }
    obj.insert("enum"_L1, arr_enum_);
    if (boolean.enumNames().has_value()) {
        QJsonArray arr_enumNames;
        const auto enumNames = *boolean.enumNames();
        for (const auto &v : enumNames) {
            arr_enumNames.append(v);
        }
        obj.insert("enumNames"_L1, arr_enumNames);
    }
    if (boolean.title().has_value()) {
        obj.insert("title"_L1, *boolean.title());
    }
    return obj;
}

std::optional<QString> McpProtocolLegacyTitledEnumSchema::defaultValue() const
{
    return mDefaultValue;
}

void McpProtocolLegacyTitledEnumSchema::setDefaultValue(std::optional<QString> newDefaultValue)
{
    mDefaultValue = std::move(newDefaultValue);
}

std::optional<QString> McpProtocolLegacyTitledEnumSchema::description() const
{
    return mDescription;
}

void McpProtocolLegacyTitledEnumSchema::setDescription(std::optional<QString> newDescription)
{
    mDescription = std::move(newDescription);
}

QStringList McpProtocolLegacyTitledEnumSchema::enums() const
{
    return mEnums;
}

void McpProtocolLegacyTitledEnumSchema::setEnums(const QStringList &newEnums)
{
    mEnums = newEnums;
}

std::optional<QStringList> McpProtocolLegacyTitledEnumSchema::enumNames() const
{
    return mEnumNames;
}

void McpProtocolLegacyTitledEnumSchema::setEnumNames(std::optional<QStringList> newEnumNames)
{
    mEnumNames = std::move(newEnumNames);
}

std::optional<QString> McpProtocolLegacyTitledEnumSchema::title() const
{
    return mTitle;
}

void McpProtocolLegacyTitledEnumSchema::setTitle(std::optional<QString> newTitle)
{
    mTitle = std::move(newTitle);
}
