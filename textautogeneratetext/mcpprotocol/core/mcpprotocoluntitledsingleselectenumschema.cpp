/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoluntitledsingleselectenumschema.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolUntitledSingleSelectEnumSchema::McpProtocolUntitledSingleSelectEnumSchema() = default;

McpProtocolUntitledSingleSelectEnumSchema::~McpProtocolUntitledSingleSelectEnumSchema() = default;

bool McpProtocolUntitledSingleSelectEnumSchema::operator==(const McpProtocolUntitledSingleSelectEnumSchema &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolUntitledSingleSelectEnumSchema &t)
{
    d.space() << "title:" << t.title();
    d.space() << "description:" << t.description();
    d.space() << "defaultValue:" << t.defaultValue();
    d.space() << "enums:" << t.enums();
    return d;
}

QByteArray McpProtocolUntitledSingleSelectEnumSchema::type()
{
    return QByteArrayLiteral("string");
}

McpProtocolUntitledSingleSelectEnumSchema McpProtocolUntitledSingleSelectEnumSchema::fromJson(const QJsonObject &obj)
{
    McpProtocolUntitledSingleSelectEnumSchema prompt;
    if (obj.value("type"_L1).toString() != QString::fromLatin1(McpProtocolUntitledSingleSelectEnumSchema::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolUntitledSingleSelectEnumSchema: type is not correct " << obj.value("type"_L1).toString();
        return {};
    }

    if (obj.contains("default"_L1)) {
        prompt.setDefaultValue(obj.value("default"_L1).toString());
    }
    if (obj.contains("description"_L1)) {
        prompt.setDescription(obj.value("description"_L1).toString());
    }
    if (obj.contains("title"_L1)) {
        prompt.setTitle(obj.value("title"_L1).toString());
    }
    if (obj.contains("enum"_L1) && obj["enum"_L1].isArray()) {
        const QJsonArray arr = obj["enum"_L1].toArray();
        QStringList lst;
        for (const QJsonValue &v : arr) {
            lst.append(v.toString());
        }
        prompt.setEnums(lst);
    }
    return prompt;
}

QJsonObject McpProtocolUntitledSingleSelectEnumSchema::toJson(const McpProtocolUntitledSingleSelectEnumSchema &boolean)
{
    QJsonObject obj;
    obj["type"_L1] = QString::fromLatin1(McpProtocolUntitledSingleSelectEnumSchema::type());
    if (boolean.defaultValue().has_value()) {
        obj["default"_L1] = *boolean.defaultValue();
    }
    if (boolean.description().has_value()) {
        obj["description"_L1] = *boolean.description();
    }
    if (boolean.title().has_value()) {
        obj["title"_L1] = *boolean.title();
    }
    QJsonArray enumArray;
    for (const auto &v : boolean.enums()) {
        enumArray.append(v);
    }
    obj["enum"_L1] = enumArray;

    return obj;
}

std::optional<QString> McpProtocolUntitledSingleSelectEnumSchema::description() const
{
    return mDescription;
}

void McpProtocolUntitledSingleSelectEnumSchema::setDescription(std::optional<QString> newDescription)
{
    mDescription = std::move(newDescription);
}

std::optional<QString> McpProtocolUntitledSingleSelectEnumSchema::title() const
{
    return mTitle;
}

void McpProtocolUntitledSingleSelectEnumSchema::setTitle(std::optional<QString> newTitle)
{
    mTitle = std::move(newTitle);
}

std::optional<QString> McpProtocolUntitledSingleSelectEnumSchema::defaultValue() const
{
    return mDefaultValue;
}

void McpProtocolUntitledSingleSelectEnumSchema::setDefaultValue(std::optional<QString> newDefaultValue)
{
    mDefaultValue = std::move(newDefaultValue);
}

QStringList McpProtocolUntitledSingleSelectEnumSchema::enums() const
{
    return mEnums;
}

void McpProtocolUntitledSingleSelectEnumSchema::setEnums(const QStringList &newEnums)
{
    mEnums = newEnums;
}
