/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltitledsingleselectenumschema.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolTitledSingleSelectEnumSchema::McpProtocolTitledSingleSelectEnumSchema() = default;

McpProtocolTitledSingleSelectEnumSchema::~McpProtocolTitledSingleSelectEnumSchema() = default;

bool McpProtocolTitledSingleSelectEnumSchema::operator==(const McpProtocolTitledSingleSelectEnumSchema &other) const = default;

bool McpProtocolTitledSingleSelectEnumSchema::OneOfItem::operator==(const McpProtocolTitledSingleSelectEnumSchema::OneOfItem &other) const = default;

QString McpProtocolTitledSingleSelectEnumSchema::OneOfItem::constValue() const
{
    return mConstValue;
}

void McpProtocolTitledSingleSelectEnumSchema::OneOfItem::setConstValue(const QString &newConstValue)
{
    mConstValue = newConstValue;
}

QString McpProtocolTitledSingleSelectEnumSchema::OneOfItem::title() const
{
    return mTitle;
}

void McpProtocolTitledSingleSelectEnumSchema::OneOfItem::setTitle(const QString &newTitle)
{
    mTitle = newTitle;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolTitledSingleSelectEnumSchema::OneOfItem &t)
{
    d.space() << "title:" << t.title();
    d.space() << "constValue:" << t.constValue();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolTitledSingleSelectEnumSchema &t)
{
    d.space() << "default:" << t.defaultValue();
    d.space() << "description:" << t.description();
    d.space() << "title:" << t.title();
    d.space() << "oneOf:" << t.oneOf();
    return d;
}

McpProtocolTitledSingleSelectEnumSchema::OneOfItem McpProtocolTitledSingleSelectEnumSchema::OneOfItem::fromJson(const QJsonObject &obj)
{
    if (!obj.contains("const"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: const";
        return {};
    }
    if (!obj.contains("title"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: title";
        return {};
    }
    McpProtocolTitledSingleSelectEnumSchema::OneOfItem result;
    result.setConstValue(obj.value("const"_L1).toString());
    result.setTitle(obj.value("title"_L1).toString());
    return result;
}

QJsonObject McpProtocolTitledSingleSelectEnumSchema::OneOfItem::toJson(const McpProtocolTitledSingleSelectEnumSchema::OneOfItem &image)
{
    QJsonObject obj;
    obj["const"_L1] = image.constValue();
    obj["title"_L1] = image.title();
    return obj;
}

QByteArray McpProtocolTitledSingleSelectEnumSchema::type()
{
    return "string"_ba;
}

McpProtocolTitledSingleSelectEnumSchema McpProtocolTitledSingleSelectEnumSchema::fromJson(const QJsonObject &obj)
{
    McpProtocolTitledSingleSelectEnumSchema prompt;
    if (obj.value("type"_L1).toString() != QString::fromLatin1(McpProtocolTitledSingleSelectEnumSchema::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolTitledSingleSelectEnumSchema: type is not correct " << obj.value("type"_L1).toString();
        return {};
    }
    if (!obj.contains("oneOf"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: oneOf";
        return {};
    }
    if (obj.contains("default"_L1)) {
        prompt.setDefault(obj.value("default"_L1).toString());
    }
    if (obj.contains("description"_L1)) {
        prompt.setDescription(obj.value("description"_L1).toString());
    }
    if (obj["oneOf"_L1].isArray()) {
        const QJsonArray arr = obj["oneOf"_L1].toArray();
        QList<OneOfItem> oneOf;
        oneOf.reserve(arr.count());
        for (const QJsonValue &v : arr) {
            oneOf.append(McpProtocolTitledSingleSelectEnumSchema::OneOfItem::fromJson(v.toObject()));
        }
        prompt.setOneOf(oneOf);
    }
    if (obj.contains("title"_L1)) {
        prompt.setTitle(obj.value("title"_L1).toString());
    }
    return prompt;
}

QJsonObject McpProtocolTitledSingleSelectEnumSchema::toJson(const McpProtocolTitledSingleSelectEnumSchema &schema)
{
    QJsonObject obj;
    obj["type"_L1] = QString::fromLatin1(McpProtocolTitledSingleSelectEnumSchema::type());
    QJsonArray arr_oneOf;
    for (const auto &v : schema.oneOf()) {
        arr_oneOf.append(McpProtocolTitledSingleSelectEnumSchema::OneOfItem::toJson(v));
    }
    obj.insert("oneOf"_L1, arr_oneOf);
    if (schema.defaultValue().has_value()) {
        obj.insert("default"_L1, *schema.defaultValue());
    }
    if (schema.description().has_value()) {
        obj.insert("description"_L1, *schema.description());
    }
    if (schema.title().has_value()) {
        obj.insert("title"_L1, *schema.title());
    }
    return obj;
}

std::optional<QString> McpProtocolTitledSingleSelectEnumSchema::defaultValue() const
{
    return mDefault;
}

void McpProtocolTitledSingleSelectEnumSchema::setDefault(std::optional<QString> newDefault)
{
    mDefault = std::move(newDefault);
}

std::optional<QString> McpProtocolTitledSingleSelectEnumSchema::description() const
{
    return mDescription;
}

void McpProtocolTitledSingleSelectEnumSchema::setDescription(std::optional<QString> newDescription)
{
    mDescription = std::move(newDescription);
}

QList<McpProtocolTitledSingleSelectEnumSchema::OneOfItem> McpProtocolTitledSingleSelectEnumSchema::oneOf() const
{
    return mOneOf;
}

void McpProtocolTitledSingleSelectEnumSchema::setOneOf(const QList<OneOfItem> &newOneOf)
{
    mOneOf = newOneOf;
}

std::optional<QString> McpProtocolTitledSingleSelectEnumSchema::title() const
{
    return mTitle;
}

void McpProtocolTitledSingleSelectEnumSchema::setTitle(std::optional<QString> newTitle)
{
    mTitle = std::move(newTitle);
}
