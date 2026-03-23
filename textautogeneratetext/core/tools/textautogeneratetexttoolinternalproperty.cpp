/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetexttoolinternalproperty.h"
#include <QDebug>

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
