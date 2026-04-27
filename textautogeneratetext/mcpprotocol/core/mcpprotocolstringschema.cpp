/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolstringschema.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolStringSchema::McpProtocolStringSchema() = default;

McpProtocolStringSchema::~McpProtocolStringSchema() = default;

bool McpProtocolStringSchema::operator==(const McpProtocolStringSchema &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolStringSchema &t)
{
    d.space() << "title:" << t.title();
    d.space() << "description:" << t.description();
    d.space() << "defaultValue:" << t.defaultValue();
    d.space() << "minLength:" << t.minLength();
    d.space() << "maxLength:" << t.maxLength();
    d.space() << "format:" << McpProtocolStringSchema::convertModeToString(*t.format());
    return d;
}

QByteArray McpProtocolStringSchema::type()
{
    return QByteArrayLiteral("string");
}

McpProtocolStringSchema McpProtocolStringSchema::fromJson(const QJsonObject &obj)
{
    McpProtocolStringSchema prompt;
    if (obj.value("type"_L1).toString() != QString::fromLatin1(McpProtocolStringSchema::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolStringSchema: type is not correct " << obj.value("type"_L1).toString();
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
    if (obj.contains("maxLength"_L1)) {
        prompt.setMaxLength(obj.value("maxLength"_L1).toInt());
    }
    if (obj.contains("minLength"_L1)) {
        prompt.setMinLength(obj.value("minLength"_L1).toInt());
    }

    if (obj.contains("format"_L1) && obj["format"_L1].isString()) {
        prompt.setFormat(convertModeFromString(obj["format"_L1].toString()));
    }
    return prompt;
}

QJsonObject McpProtocolStringSchema::toJson(const McpProtocolStringSchema &boolean)
{
    QJsonObject obj;
    obj["type"_L1] = QString::fromLatin1(McpProtocolStringSchema::type());
    if (boolean.defaultValue().has_value()) {
        obj["default"_L1] = *boolean.defaultValue();
    }
    if (boolean.description().has_value()) {
        obj["description"_L1] = *boolean.description();
    }
    if (boolean.title().has_value()) {
        obj["title"_L1] = *boolean.title();
    }
    if (boolean.format().has_value()) {
        obj["format"_L1] = McpProtocolStringSchema::convertModeToString(*boolean.format());
    }
    if (boolean.maxLength().has_value()) {
        obj["maxLength"_L1] = *boolean.maxLength();
    }
    if (boolean.minLength().has_value()) {
        obj["minLength"_L1] = *boolean.minLength();
    }
    return obj;
}

std::optional<QString> McpProtocolStringSchema::description() const
{
    return mDescription;
}

void McpProtocolStringSchema::setDescription(std::optional<QString> newDescription)
{
    mDescription = std::move(newDescription);
}

std::optional<QString> McpProtocolStringSchema::title() const
{
    return mTitle;
}

void McpProtocolStringSchema::setTitle(std::optional<QString> newTitle)
{
    mTitle = std::move(newTitle);
}

std::optional<bool> McpProtocolStringSchema::defaultValue() const
{
    return mDefaultValue;
}

void McpProtocolStringSchema::setDefaultValue(std::optional<bool> newDefaultValue)
{
    mDefaultValue = newDefaultValue;
}

std::optional<int> McpProtocolStringSchema::minLength() const
{
    return mMinLength;
}

void McpProtocolStringSchema::setMinLength(std::optional<int> newMinLength)
{
    mMinLength = newMinLength;
}

std::optional<int> McpProtocolStringSchema::maxLength() const
{
    return mMaxLength;
}

void McpProtocolStringSchema::setMaxLength(std::optional<int> newMaxLength)
{
    mMaxLength = newMaxLength;
}

std::optional<McpProtocolStringSchema::Format> McpProtocolStringSchema::format() const
{
    return mFormat;
}

void McpProtocolStringSchema::setFormat(std::optional<Format> newFormat)
{
    mFormat = newFormat;
}

QString McpProtocolStringSchema::convertModeToString(McpProtocolStringSchema::Format mode)
{
    switch (mode) {
    case Format::Date:
        return u"date"_s;
    case Format::Dateminustime:
        return u"dateminustime"_s;
    case Format::Email:
        return u"email"_s;
    case Format::Uri:
        return u"uri"_s;
    case Format::Unknown:
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << " Not defined mode";
        return {};
    }
    return {};
}

McpProtocolStringSchema::Format McpProtocolStringSchema::convertModeFromString(const QString &str)
{
    if (str == "date"_L1) {
        return Format::Date;
    } else if (str == "dateminustime"_L1) {
        return Format::Dateminustime;
    } else if (str == "email"_L1) {
        return Format::Email;
    } else if (str == "uri"_L1) {
        return Format::Uri;
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << " Str is not supported " << str;
        return Format::Unknown;
    }
}
