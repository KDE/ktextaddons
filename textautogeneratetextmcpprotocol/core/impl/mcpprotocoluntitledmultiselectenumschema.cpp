/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoluntitledmultiselectenumschema.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolUntitledMultiSelectEnumSchema::McpProtocolUntitledMultiSelectEnumSchema() = default;

McpProtocolUntitledMultiSelectEnumSchema::~McpProtocolUntitledMultiSelectEnumSchema() = default;

bool McpProtocolUntitledMultiSelectEnumSchema::operator==(const McpProtocolUntitledMultiSelectEnumSchema &other) const = default;
QStringList McpProtocolUntitledMultiSelectEnumSchema::Items::enumValue() const
{
    return mEnum;
}

void McpProtocolUntitledMultiSelectEnumSchema::Items::setEnum(const QStringList &newEnum)
{
    mEnum = newEnum;
}

bool McpProtocolUntitledMultiSelectEnumSchema::Items::operator==(const McpProtocolUntitledMultiSelectEnumSchema::Items &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolUntitledMultiSelectEnumSchema &t)
{
    return d;
}

McpProtocolUntitledMultiSelectEnumSchema::Items McpProtocolUntitledMultiSelectEnumSchema::Items::fromJson(const QJsonObject &obj)
{
    if (!obj.contains("enum"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: enum";
        return {};
    }
    if (!obj.contains("type"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: type";
        return {};
    }
    McpProtocolUntitledMultiSelectEnumSchema::Items result;
    if (obj.value("type"_L1).toString() != u"string"_s) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'type' must be 'string', got: " << obj.value("type"_L1).toString();
        return {};
    }
    if (obj.contains("enum"_L1) && obj["enum"_L1].isArray()) {
        const QJsonArray arr = obj["enum"_L1].toArray();
        QStringList lst;
        for (const QJsonValue &v : arr) {
            lst.append(v.toString());
        }
        result.setEnum(lst);
    }
    return result;
}

QJsonObject McpProtocolUntitledMultiSelectEnumSchema::Items::toJson(const McpProtocolUntitledMultiSelectEnumSchema::Items &image)
{
    QJsonObject obj;
    obj["type"_L1] = u"string"_s;
    QJsonArray arr_enum;
    for (const auto &v : image.enumValue()) {
        arr_enum.append(v);
    }
    obj["enum"_L1] = arr_enum;
    return obj;
}

QByteArray McpProtocolUntitledMultiSelectEnumSchema::type()
{
    return "array"_ba;
}

McpProtocolUntitledMultiSelectEnumSchema McpProtocolUntitledMultiSelectEnumSchema::fromJson(const QJsonObject &obj)
{
    McpProtocolUntitledMultiSelectEnumSchema prompt;
    if (obj.value("type"_L1).toString() != QString::fromLatin1(McpProtocolUntitledMultiSelectEnumSchema::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolUntitledMultiSelectEnumSchema: type is not correct " << obj.value("type"_L1).toString();
        return {};
    }
    if (!obj.contains("items"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: items";
        return {};
    }
    if (!obj.contains("type"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: type";
        return {};
    }
    if (obj.contains("default"_L1) && obj["default"_L1].isArray()) {
        const QJsonArray arr = obj["default"_L1].toArray();
        QStringList list_default;
        for (const QJsonValue &v : arr) {
            list_default.append(v.toString());
        }
        prompt.setDefault(list_default);
    }
    if (obj.contains("description"_L1)) {
        prompt.setDescription(obj.value("description"_L1).toString());
    }
    if (obj.contains("items"_L1) && obj["items"_L1].isObject()) {
        prompt.setItems(McpProtocolUntitledMultiSelectEnumSchema::Items::fromJson(obj["items"_L1].toObject()));
    }
    if (obj.contains("maxItems"_L1)) {
        prompt.setMaxItems(obj.value("maxItems"_L1).toInt());
    }
    if (obj.contains("minItems"_L1)) {
        prompt.setMinItems(obj.value("minItems"_L1).toInt());
    }
    if (obj.contains("title"_L1)) {
        prompt.setTitle(obj.value("title"_L1).toString());
    }
    return prompt;
}

QJsonObject McpProtocolUntitledMultiSelectEnumSchema::toJson(const McpProtocolUntitledMultiSelectEnumSchema &schema)
{
    QJsonObject obj;
    obj["type"_L1] = QString::fromLatin1(McpProtocolUntitledMultiSelectEnumSchema::type());
    obj["items"_L1] = McpProtocolUntitledMultiSelectEnumSchema::Items::toJson(schema.items());
    if (schema.defaultValue().has_value()) {
        QJsonArray arr_default;
        const auto defaultValue = *schema.defaultValue();
        for (const auto &v : defaultValue) {
            arr_default.append(v);
        }
        obj.insert("default"_L1, arr_default);
    }
    if (schema.description().has_value()) {
        obj.insert("description"_L1, *schema.description());
    }
    if (schema.maxItems().has_value()) {
        obj.insert("maxItems"_L1, *schema.maxItems());
    }
    if (schema.minItems().has_value()) {
        obj.insert("minItems"_L1, *schema.minItems());
    }
    if (schema.title().has_value()) {
        obj.insert("title"_L1, *schema.title());
    }
    return obj;
}

std::optional<QStringList> McpProtocolUntitledMultiSelectEnumSchema::defaultValue() const
{
    return mDefault;
}

void McpProtocolUntitledMultiSelectEnumSchema::setDefault(std::optional<QStringList> newDefault)
{
    mDefault = std::move(newDefault);
}

std::optional<QString> McpProtocolUntitledMultiSelectEnumSchema::description() const
{
    return mDescription;
}

void McpProtocolUntitledMultiSelectEnumSchema::setDescription(std::optional<QString> newDescription)
{
    mDescription = std::move(newDescription);
}

McpProtocolUntitledMultiSelectEnumSchema::Items McpProtocolUntitledMultiSelectEnumSchema::items() const
{
    return mItems;
}

void McpProtocolUntitledMultiSelectEnumSchema::setItems(const Items &newItems)
{
    mItems = newItems;
}

std::optional<int> McpProtocolUntitledMultiSelectEnumSchema::maxItems() const
{
    return mMaxItems;
}

void McpProtocolUntitledMultiSelectEnumSchema::setMaxItems(std::optional<int> newMaxItems)
{
    mMaxItems = std::move(newMaxItems);
}

std::optional<int> McpProtocolUntitledMultiSelectEnumSchema::minItems() const
{
    return mMinItems;
}

void McpProtocolUntitledMultiSelectEnumSchema::setMinItems(std::optional<int> newMinItems)
{
    mMinItems = std::move(newMinItems);
}

std::optional<QString> McpProtocolUntitledMultiSelectEnumSchema::title() const
{
    return mTitle;
}

void McpProtocolUntitledMultiSelectEnumSchema::setTitle(std::optional<QString> newTitle)
{
    mTitle = std::move(newTitle);
}
