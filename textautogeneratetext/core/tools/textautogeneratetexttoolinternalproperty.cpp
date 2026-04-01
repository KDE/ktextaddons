/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetexttoolinternalproperty.h"
#include "textautogeneratetextcore_debug.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTextToolInternalProperty::TextAutoGenerateTextToolInternalProperty() = default;

TextAutoGenerateTextToolInternalProperty::~TextAutoGenerateTextToolInternalProperty() = default;

bool TextAutoGenerateTextToolInternalProperty::operator==(const TextAutoGenerateTextToolInternalProperty &other) const
{
    return mTypeElements == other.typeElements() && mDescription == other.description() && mName == other.name() && mPropertyType == other.propertyType();
}

TextAutoGenerateTextToolInternalProperty::PropertyType TextAutoGenerateTextToolInternalProperty::propertyType() const
{
    return mPropertyType;
}

void TextAutoGenerateTextToolInternalProperty::setPropertyType(PropertyType newPropertyType)
{
    mPropertyType = newPropertyType;
}

QStringList TextAutoGenerateTextToolInternalProperty::typeElements() const
{
    return mTypeElements;
}

void TextAutoGenerateTextToolInternalProperty::setTypeElements(const QStringList &newTypeElements)
{
    mTypeElements = newTypeElements;
}

QString TextAutoGenerateTextToolInternalProperty::description() const
{
    return mDescription;
}

void TextAutoGenerateTextToolInternalProperty::setDescription(const QString &newDescription)
{
    mDescription = newDescription;
}

QString TextAutoGenerateTextToolInternalProperty::name() const
{
    return mName;
}

void TextAutoGenerateTextToolInternalProperty::setName(const QString &newName)
{
    mName = newName;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty &t)
{
    d.space() << "name:" << t.name();
    d.space() << "description:" << t.description();
    d.space() << "typeElements:" << t.typeElements();
    d.space() << "propertyType:" << t.propertyType();
    return d;
}

bool TextAutoGenerateTextToolInternalProperty::isValid() const
{
    return !mName.isEmpty();
}

void TextAutoGenerateTextToolInternalProperty::parse(const QJsonObject &obj, const QString &name)
{
    mDescription = obj["description"_L1].toString();
    mTypeElements.clear();
    mName = name;
    if (obj.contains("enum"_L1)) {
        const QJsonArray enumArray = obj["enum"_L1].toArray();
        for (const auto &v : enumArray) {
            mTypeElements.append(v.toString());
        }
    }
    mPropertyType = TextAutoGenerateTextToolInternalProperty::convertPropertyTypeFromString(obj["type"_L1].toString());
    // qDebug() << " parse tool " << *this;
}

QString TextAutoGenerateTextToolInternalProperty::convertPropertyTypeToString(TextAutoGenerateTextToolInternalProperty::PropertyType type)
{
    switch (type) {
    case PropertyType::String:
        return u"string"_s;
    case PropertyType::Number:
        return u"number"_s;
    case PropertyType::Integer:
        return u"integer"_s;
    case PropertyType::Boolean:
        return u"boolean"_s;
    }
    qCDebug(TEXTAUTOGENERATETEXT_CORE_LOG) << "invalid type " << type;
    return {};
}

TextAutoGenerateTextToolInternalProperty::PropertyType TextAutoGenerateTextToolInternalProperty::convertPropertyTypeFromString(const QString &str)
{
    if (str == "string"_L1) {
        return PropertyType::String;
    } else if (str == "number"_L1) {
        return PropertyType::Number;
    } else if (str == "integer"_L1) {
        return PropertyType::Integer;
    } else if (str == "boolean"_L1) {
        return PropertyType::Boolean;
    } else {
        qCDebug(TEXTAUTOGENERATETEXT_CORE_LOG) << "Invalid type :" << str;
        return PropertyType::String;
    }
}

#include "moc_textautogeneratetexttoolinternalproperty.cpp"
