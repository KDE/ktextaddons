/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetexttoolinternalproperty.h"
#include <QDebug>
#include <QJsonObject>

using namespace TextAutoGenerateText;
TextAutoGenerateTextToolInternalProperty::TextAutoGenerateTextToolInternalProperty() = default;

TextAutoGenerateTextToolInternalProperty::~TextAutoGenerateTextToolInternalProperty() = default;

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
    return d;
}

bool TextAutoGenerateTextToolInternalProperty::isValid() const
{
    return !mName.isEmpty();
}

void TextAutoGenerateTextToolInternalProperty::parse(const QJsonObject &obj)
{
#if 0
    const QJsonObject function = obj["function"_L1].toObject();
    mDescription = function["description"_L1].toString();
    mName = function["name"_L1].toString();

    const QJsonObject parameters = function["parameters"_L1].toObject();
    const QJsonObject properties = parameters["properties"_L1].toObject();
    const QJsonObject required = parameters["required"_L1].toObject();
    const QStringList keys = properties.keys();
    for (const QString &k : keys) {
        KAITodoToolProperty property;
        property.parse(properties[k].toObject(), k);
        if (property.isValid()) {
            mProperties.append(property);
        }
    }
    // qDebug() << " parse tool " << *this;
#endif
}
