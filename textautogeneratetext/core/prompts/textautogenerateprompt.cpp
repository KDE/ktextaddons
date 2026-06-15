/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateprompt.h"

using namespace TextAutoGenerateText;
TextAutoGeneratePrompt::TextAutoGeneratePrompt() = default;
TextAutoGeneratePrompt::~TextAutoGeneratePrompt() = default;

QString TextAutoGeneratePrompt::name() const
{
    return mName;
}

void TextAutoGeneratePrompt::setName(const QString &newName)
{
    mName = newName;
}

QString TextAutoGeneratePrompt::text() const
{
    return mText;
}

void TextAutoGeneratePrompt::setText(const QString &newText)
{
    mText = newText;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGeneratePrompt &t)
{
    d.space() << "name:" << t.name();
    d.space() << "text" << t.text();
    return d;
}
