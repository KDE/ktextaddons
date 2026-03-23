/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetexttoolinternalproperty.h"
#include <QDebug>

using namespace TextAutoGenerateText;
TextAutoGenerateTextToolInternalProperty::TextAutoGenerateTextToolInternalProperty() = default;

TextAutoGenerateTextToolInternalProperty::~TextAutoGenerateTextToolInternalProperty() = default;

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty &t)
{
    return d;
}
