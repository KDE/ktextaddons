/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetexttoolpluginproperty.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextToolPluginProperty::TextAutoGenerateTextToolPluginProperty() = default;

TextAutoGenerateTextToolPluginProperty::~TextAutoGenerateTextToolPluginProperty() = default;

QString TextAutoGenerateTextToolPluginProperty::description() const
{
    return mDescription;
}

void TextAutoGenerateTextToolPluginProperty::setDescription(const QString &newDescription)
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
