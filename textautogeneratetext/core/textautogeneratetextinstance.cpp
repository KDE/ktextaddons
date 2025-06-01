/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstance.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextInstance::TextAutoGenerateTextInstance() = default;

TextAutoGenerateTextInstance::~TextAutoGenerateTextInstance() = default;

QString TextAutoGenerateTextInstance::name() const
{
    return mName;
}

void TextAutoGenerateTextInstance::setName(const QString &newName)
{
    mName = newName;
}
