/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetexttoolpluginproperty.h"

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
    return d;
}
