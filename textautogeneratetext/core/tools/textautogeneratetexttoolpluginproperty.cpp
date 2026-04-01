/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetexttoolpluginproperty.h"
#include "textautogeneratetextcore_debug.h"
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateTextToolPluginProperty::TextAutoGenerateTextToolPluginProperty() = default;

TextAutoGenerateTextToolPluginProperty::~TextAutoGenerateTextToolPluginProperty() = default;

KLazyLocalizedString TextAutoGenerateTextToolPluginProperty::description() const
{
    return mDescription;
}

void TextAutoGenerateTextToolPluginProperty::setDescription(const KLazyLocalizedString &newDescription)
{
    mDescription = newDescription;
}

QString TextAutoGenerateTextToolPluginProperty::name() const
{
    return mName;
}

void TextAutoGenerateTextToolPluginProperty::setName(const QString &newName)
{
    mName = newName;
}

QStringList TextAutoGenerateTextToolPluginProperty::typeElements() const
{
    return mTypeElements;
}

void TextAutoGenerateTextToolPluginProperty::setTypeElements(const QStringList &newEnumElements)
{
    mTypeElements = newEnumElements;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty &t)
{
    d.space() << "typeElements:" << t.typeElements();
    d.space() << "description:" << t.description().untranslatedText();
    d.space() << "name:" << t.name();
    d.space() << "propertyType:" << t.propertyType();
    return d;
}

QString TextAutoGenerateTextToolPluginProperty::convertPropertyTypeToString(TextAutoGenerateTextToolPluginProperty::PropertyType type)
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

TextAutoGenerateTextToolPluginProperty::PropertyType TextAutoGenerateTextToolPluginProperty::convertPropertyTypeFromString(const QString &str)
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

TextAutoGenerateTextToolPluginProperty::PropertyType TextAutoGenerateTextToolPluginProperty::propertyType() const
{
    return mPropertyType;
}

void TextAutoGenerateTextToolPluginProperty::setPropertyType(PropertyType newPropertyType)
{
    mPropertyType = newPropertyType;
}

#include "moc_textautogeneratetexttoolpluginproperty.cpp"
