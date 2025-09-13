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

KLazyLocalizedString TextAutoGenerateTextToolPluginProperty::name() const
{
    return mName;
}

void TextAutoGenerateTextToolPluginProperty::setName(const KLazyLocalizedString &newName)
{
    mName = newName;
}

QByteArray TextAutoGenerateTextToolPluginProperty::generateProperty() const
{
#if 0
    "location": {
      "type": "string",
      "description": "The location to get the weather for, e.g. San Francisco, CA"
    },
#endif
    return QByteArray(mName.untranslatedText()) + ":{"_ba + "type: \"string\","_ba + "description: \""_ba + QByteArray(mDescription.untranslatedText())
        + "\"}"_ba;
}
