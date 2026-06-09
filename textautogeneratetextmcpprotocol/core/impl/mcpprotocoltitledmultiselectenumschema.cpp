/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltitledmultiselectenumschema.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolTitledMultiSelectEnumSchema::McpProtocolTitledMultiSelectEnumSchema() = default;

McpProtocolTitledMultiSelectEnumSchema::~McpProtocolTitledMultiSelectEnumSchema() = default;

bool McpProtocolTitledMultiSelectEnumSchema::operator==(const McpProtocolTitledMultiSelectEnumSchema &other) const = default;

bool McpProtocolTitledMultiSelectEnumSchema::Items::operator==(const McpProtocolTitledMultiSelectEnumSchema::Items &other) const = default;

QString McpProtocolTitledMultiSelectEnumSchema::Items::AnyOfItem::constValue() const
{
    return mConstValue;
}

void McpProtocolTitledMultiSelectEnumSchema::Items::AnyOfItem::setConstValue(const QString &newConstValue)
{
    mConstValue = newConstValue;
}

QString McpProtocolTitledMultiSelectEnumSchema::Items::AnyOfItem::title() const
{
    return mTitle;
}

void McpProtocolTitledMultiSelectEnumSchema::Items::AnyOfItem::setTitle(const QString &newTitle)
{
    mTitle = newTitle;
}

bool McpProtocolTitledMultiSelectEnumSchema::Items::AnyOfItem::operator==(const McpProtocolTitledMultiSelectEnumSchema::Items::AnyOfItem &other) const =
    default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolTitledMultiSelectEnumSchema::Items::AnyOfItem &t)
{
    d.space() << "title:" << t.title();
    d.space() << "constValue:" << t.constValue();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolTitledMultiSelectEnumSchema::Items &t)
{
    d.space() << "anyOf:" << t.anyOf();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolTitledMultiSelectEnumSchema &t)
{
    d.space() << "default:" << t.defaultValue();
    d.space() << "description:" << t.description();
    d.space() << "minItems:" << t.minItems();
    d.space() << "maxItems:" << t.maxItems();
    d.space() << "title:" << t.title();
    d.space() << "items:" << t.items();
    return d;
}

QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolTitledMultiSelectEnumSchema::Items::AnyOfItem>
TextAutoGenerateTextMcpProtocolCore::McpProtocolTitledMultiSelectEnumSchema::Items::anyOf() const
{
    return mAnyOf;
}

void TextAutoGenerateTextMcpProtocolCore::McpProtocolTitledMultiSelectEnumSchema::Items::setAnyOf(const QList<AnyOfItem> &newAnyOf)
{
    mAnyOf = newAnyOf;
}

McpProtocolTitledMultiSelectEnumSchema::Items::AnyOfItem McpProtocolTitledMultiSelectEnumSchema::Items::AnyOfItem::fromJson(const QJsonObject &obj)
{
    if (!obj.contains("const"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: const";
        return {};
    }
    if (!obj.contains("title"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: title";
        return {};
    }
    McpProtocolTitledMultiSelectEnumSchema::Items::AnyOfItem result;
    result.setConstValue(obj.value("const"_L1).toString());
    result.setTitle(obj.value("title"_L1).toString());
    return result;
}

QJsonObject McpProtocolTitledMultiSelectEnumSchema::Items::AnyOfItem::toJson(const McpProtocolTitledMultiSelectEnumSchema::Items::AnyOfItem &image)
{
    QJsonObject obj;
    obj["const"_L1] = image.constValue();
    obj["title"_L1] = image.title();
    return obj;
}

McpProtocolTitledMultiSelectEnumSchema::Items McpProtocolTitledMultiSelectEnumSchema::Items::fromJson(const QJsonObject &obj)
{
    if (!obj.contains("anyOf"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: anyOf";
        return {};
    }
    McpProtocolTitledMultiSelectEnumSchema::Items result;
    if (obj.contains("anyOf"_L1) && obj["anyOf"_L1].isArray()) {
        QList<AnyOfItem> anyOf;
        const QJsonArray arr = obj["anyOf"_L1].toArray();
        for (const QJsonValue &v : arr) {
            anyOf.append(McpProtocolTitledMultiSelectEnumSchema::Items::AnyOfItem::fromJson(v.toObject()));
        }
        result.setAnyOf(anyOf);
    }
    return result;
}

QJsonObject McpProtocolTitledMultiSelectEnumSchema::Items::toJson(const McpProtocolTitledMultiSelectEnumSchema::Items &image)
{
    QJsonObject obj;
    QJsonArray arr_anyOf;
    for (const auto &v : image.anyOf()) {
        arr_anyOf.append(McpProtocolTitledMultiSelectEnumSchema::Items::AnyOfItem::toJson(v));
    }
    obj.insert("anyOf"_L1, arr_anyOf);
    return obj;
}

QByteArray McpProtocolTitledMultiSelectEnumSchema::type()
{
    return "array"_ba;
}

McpProtocolTitledMultiSelectEnumSchema McpProtocolTitledMultiSelectEnumSchema::fromJson(const QJsonObject &obj)
{
    McpProtocolTitledMultiSelectEnumSchema prompt;
    if (obj.value("type"_L1).toString() != QString::fromLatin1(McpProtocolTitledMultiSelectEnumSchema::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolTitledMultiSelectEnumSchema: type is not correct " << obj.value("type"_L1).toString();
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
        prompt.setItems(McpProtocolTitledMultiSelectEnumSchema::Items::fromJson(obj["items"_L1].toObject()));
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

QJsonObject McpProtocolTitledMultiSelectEnumSchema::toJson(const McpProtocolTitledMultiSelectEnumSchema &schema)
{
    QJsonObject obj;
    obj["type"_L1] = QString::fromLatin1(McpProtocolTitledMultiSelectEnumSchema::type());
    obj["items"_L1] = McpProtocolTitledMultiSelectEnumSchema::Items::toJson(schema.items());
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

std::optional<QStringList> McpProtocolTitledMultiSelectEnumSchema::defaultValue() const
{
    return mDefault;
}

void McpProtocolTitledMultiSelectEnumSchema::setDefault(std::optional<QStringList> newDefault)
{
    mDefault = std::move(newDefault);
}

std::optional<QString> McpProtocolTitledMultiSelectEnumSchema::description() const
{
    return mDescription;
}

void McpProtocolTitledMultiSelectEnumSchema::setDescription(std::optional<QString> newDescription)
{
    mDescription = std::move(newDescription);
}

McpProtocolTitledMultiSelectEnumSchema::Items McpProtocolTitledMultiSelectEnumSchema::items() const
{
    return mItems;
}

void McpProtocolTitledMultiSelectEnumSchema::setItems(const Items &newItems)
{
    mItems = newItems;
}

std::optional<int> McpProtocolTitledMultiSelectEnumSchema::maxItems() const
{
    return mMaxItems;
}

void McpProtocolTitledMultiSelectEnumSchema::setMaxItems(std::optional<int> newMaxItems)
{
    mMaxItems = newMaxItems;
}

std::optional<int> McpProtocolTitledMultiSelectEnumSchema::minItems() const
{
    return mMinItems;
}

void McpProtocolTitledMultiSelectEnumSchema::setMinItems(std::optional<int> newMinItems)
{
    mMinItems = newMinItems;
}

std::optional<QString> McpProtocolTitledMultiSelectEnumSchema::title() const
{
    return mTitle;
}

void McpProtocolTitledMultiSelectEnumSchema::setTitle(std::optional<QString> newTitle)
{
    mTitle = std::move(newTitle);
}
