/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetexttoolinternalproperty.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
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
    // qDebug() << " parse tool " << *this;
}
