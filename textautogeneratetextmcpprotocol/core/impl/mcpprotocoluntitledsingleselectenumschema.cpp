/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoluntitledsingleselectenumschema.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolUntitledSingleSelectEnumSchema::McpProtocolUntitledSingleSelectEnumSchema() = default;

bool McpProtocolUntitledSingleSelectEnumSchema::operator==(const McpProtocolUntitledSingleSelectEnumSchema &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolUntitledSingleSelectEnumSchema &t)
{
    d.space() << "title:" << t.title();
    d.space() << "description:" << t.description();
    d.space() << "defaultValue:" << t.defaultValue();
    d.space() << "enums:" << t.enums();
    return d;
}

QByteArray McpProtocolUntitledSingleSelectEnumSchema::type()
{
    return "string"_ba;
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
    if (const QJsonValue enumValue = obj.value("enum"_L1); enumValue.isArray()) {
        const QJsonArray arr = enumValue.toArray();
        QStringList lst;
        lst.reserve(arr.count());
        for (const auto &v : arr) {
            lst.append(v.toString());
        }
        prompt.setEnums(std::move(lst));
    }
    return prompt;
}

QJsonObject McpProtocolUntitledSingleSelectEnumSchema::toJson(const McpProtocolUntitledSingleSelectEnumSchema &untitledSingleSelectEnumSchema)
{
    QJsonObject obj;
    obj["type"_L1] = QString::fromLatin1(McpProtocolUntitledSingleSelectEnumSchema::type());
    if (untitledSingleSelectEnumSchema.defaultValue().has_value()) {
        obj["default"_L1] = *untitledSingleSelectEnumSchema.defaultValue();
    }
    if (untitledSingleSelectEnumSchema.description().has_value()) {
        obj["description"_L1] = *untitledSingleSelectEnumSchema.description();
    }
    if (untitledSingleSelectEnumSchema.title().has_value()) {
        obj["title"_L1] = *untitledSingleSelectEnumSchema.title();
    }
    obj["enum"_L1] = QJsonArray::fromStringList(untitledSingleSelectEnumSchema.enums());

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

void McpProtocolUntitledSingleSelectEnumSchema::setEnums(QStringList newEnums)
{
    mEnums = std::move(newEnums);
}
