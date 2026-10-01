/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocollegacytitledenumschema.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolLegacyTitledEnumSchema::McpProtocolLegacyTitledEnumSchema() = default;

bool McpProtocolLegacyTitledEnumSchema::operator==(const McpProtocolLegacyTitledEnumSchema &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolLegacyTitledEnumSchema &t)
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
    return "string"_ba;
}

McpProtocolLegacyTitledEnumSchema McpProtocolLegacyTitledEnumSchema::fromJson(const QJsonObject &obj)
{
    if (obj.value("type"_L1).toString() != QString::fromLatin1(McpProtocolLegacyTitledEnumSchema::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolLegacyTitledEnumSchema: field 'type' must be" << McpProtocolLegacyTitledEnumSchema::type()
                                                       << "got:" << obj.value("type"_L1).toString();
        return {};
    }
    McpProtocolLegacyTitledEnumSchema schema;
    if (obj.contains("default"_L1)) {
        schema.setDefaultValue(obj.value("default"_L1).toString());
    }
    if (obj.contains("description"_L1)) {
        schema.setDescription(obj.value("description"_L1).toString());
    }
    if (const QJsonValue enumValue = obj.value("enum"_L1); enumValue.isArray()) {
        const QJsonArray arr = enumValue.toArray();
        QStringList lst;
        lst.reserve(arr.count());
        for (const auto &v : arr) {
            lst.append(v.toString());
        }
        schema.setEnums(std::move(lst));
    }
    if (const QJsonValue enumNamesValue = obj.value("enumNames"_L1); enumNamesValue.isArray()) {
        const QJsonArray arr = enumNamesValue.toArray();
        QStringList list_enumNames;
        list_enumNames.reserve(arr.count());
        for (const auto &v : arr) {
            list_enumNames.append(v.toString());
        }
        schema.setEnumNames(std::move(list_enumNames));
    }

    if (obj.contains("title"_L1)) {
        schema.setTitle(obj.value("title"_L1).toString());
    }
    return schema;
}

QJsonObject McpProtocolLegacyTitledEnumSchema::toJson(const McpProtocolLegacyTitledEnumSchema &schema)
{
    QJsonObject obj;
    obj["type"_L1] = QString::fromLatin1(type());
    if (schema.defaultValue().has_value()) {
        obj.insert("default"_L1, *schema.defaultValue());
    }
    if (schema.description().has_value()) {
        obj.insert("description"_L1, *schema.description());
    }
    QJsonArray arr_enum_;
    for (const auto &v : schema.enums()) {
        arr_enum_.append(v);
    }
    obj.insert("enum"_L1, arr_enum_);
    if (schema.enumNames().has_value()) {
        QJsonArray arr_enumNames;
        const auto enumNames = *schema.enumNames();
        for (const auto &v : enumNames) {
            arr_enumNames.append(v);
        }
        obj.insert("enumNames"_L1, arr_enumNames);
    }
    if (schema.title().has_value()) {
        obj.insert("title"_L1, *schema.title());
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

void McpProtocolLegacyTitledEnumSchema::setEnums(QStringList newEnums)
{
    mEnums = std::move(newEnums);
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
