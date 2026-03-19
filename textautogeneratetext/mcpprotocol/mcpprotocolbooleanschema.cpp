/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolbooleanschema.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolBooleanSchema::McpProtocolBooleanSchema() = default;

McpProtocolBooleanSchema::~McpProtocolBooleanSchema() = default;

bool McpProtocolBooleanSchema::operator==(const McpProtocolBooleanSchema &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolBooleanSchema &t)
{
    d.space() << "title:" << t.title();
    d.space() << "description:" << t.description();
    d.space() << "defaultValue:" << t.defaultValue();
    return d;
}

QByteArray McpProtocolBooleanSchema::type()
{
    return QByteArrayLiteral("boolean");
}

McpProtocolBooleanSchema McpProtocolBooleanSchema::fromJson(const QJsonObject &obj)
{
    McpProtocolBooleanSchema prompt;
    if (obj.value("type"_L1).toString() != QString::fromLatin1(McpProtocolBooleanSchema::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "McpProtocolBooleanSchema: type is not correct " << obj.value("type"_L1).toString();
        return {};
    }

    if (obj.contains("default"_L1)) {
        prompt.setDefaultValue(obj.value("default"_L1).toBool());
    }
    if (obj.contains("description"_L1)) {
        prompt.setDescription(obj.value("description"_L1).toString());
    }
    if (obj.contains("title"_L1)) {
        prompt.setTitle(obj.value("title"_L1).toString());
    }
    return prompt;
}

QJsonObject McpProtocolBooleanSchema::toJson(const McpProtocolBooleanSchema &boolean)
{
    QJsonObject obj;
    obj["type"_L1] = QString::fromLatin1(McpProtocolBooleanSchema::type());
    if (boolean.defaultValue().has_value()) {
        obj["default"_L1] = *boolean.defaultValue();
    }
    if (boolean.description().has_value()) {
        obj["description"_L1] = *boolean.description();
    }
    if (boolean.title().has_value()) {
        obj["title"_L1] = *boolean.title();
    }
    return obj;
}

std::optional<QString> McpProtocolBooleanSchema::description() const
{
    return mDescription;
}

void McpProtocolBooleanSchema::setDescription(std::optional<QString> newDescription)
{
    mDescription = std::move(newDescription);
}

std::optional<QString> McpProtocolBooleanSchema::title() const
{
    return mTitle;
}

void McpProtocolBooleanSchema::setTitle(std::optional<QString> newTitle)
{
    mTitle = std::move(newTitle);
}

std::optional<bool> McpProtocolBooleanSchema::defaultValue() const
{
    return mDefaultValue;
}

void McpProtocolBooleanSchema::setDefaultValue(std::optional<bool> newDefaultValue)
{
    mDefaultValue = newDefaultValue;
}
