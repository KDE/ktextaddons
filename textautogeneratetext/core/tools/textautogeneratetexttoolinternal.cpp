/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetexttoolinternal.h"
#include "textautogeneratetexttoolinternalproperty.h"
#include <QDebug>
using namespace TextAutoGenerateText;
TextAutoGenerateTextToolInternal::TextAutoGenerateTextToolInternal() = default;

TextAutoGenerateTextToolInternal::~TextAutoGenerateTextToolInternal() = default;

QList<TextAutoGenerateTextToolInternalProperty> TextAutoGenerateTextToolInternal::properties() const
{
    return mProperties;
}

void TextAutoGenerateTextToolInternal::setProperties(const QList<TextAutoGenerateTextToolInternalProperty> &newProperties)
{
    mProperties = newProperties;
}

QStringList TextAutoGenerateTextToolInternal::required() const
{
    return mRequired;
}

void TextAutoGenerateTextToolInternal::setRequired(const QStringList &newRequired)
{
    mRequired = newRequired;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextToolInternal &t)
{
    d.space() << "properties:" << t.properties();
    d.space() << "required:" << t.required();
    return d;
}
