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

McpProtocolLegacyTitledEnumSchema McpProtocolLegacyTitledEnumSchema::fromJson(const QJsonObject &obj)
{
    McpProtocolLegacyTitledEnumSchema prompt;
    // TODO
    return prompt;
}

QJsonObject McpProtocolLegacyTitledEnumSchema::toJson(const McpProtocolLegacyTitledEnumSchema &boolean)
{
    QJsonObject obj;
    // TODO
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
