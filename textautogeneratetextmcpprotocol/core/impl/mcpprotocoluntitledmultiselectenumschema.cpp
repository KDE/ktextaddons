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

    return prompt;
}

QJsonObject McpProtocolUntitledMultiSelectEnumSchema::toJson(const McpProtocolUntitledMultiSelectEnumSchema &boolean)
{
    QJsonObject obj;
    obj["type"_L1] = QString::fromLatin1(McpProtocolUntitledMultiSelectEnumSchema::type());

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
