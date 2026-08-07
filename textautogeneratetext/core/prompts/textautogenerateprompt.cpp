/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateprompt.h"
#include <QDebug>

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

QString TextAutoGeneratePrompt::description() const
{
    return mDescription;
}

void TextAutoGeneratePrompt::setDescription(const QString &newDescription)
{
    mDescription = newDescription;
}

bool TextAutoGeneratePrompt::enabled() const
{
    return mEnabled;
}

void TextAutoGeneratePrompt::setEnabled(bool newEnabled)
{
    mEnabled = newEnabled;
}

TextAutoGeneratePrompt::Category TextAutoGeneratePrompt::category() const
{
    return mCategory;
}

void TextAutoGeneratePrompt::setCategory(Category newCategory)
{
    mCategory = newCategory;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGeneratePrompt &t)
{
    d.space() << "name:" << t.name();
    d.space() << "text" << t.text();
    d.space() << "description:" << t.description();
    d.space() << "enabled:" << t.enabled();
    d.space() << "category:" << t.category();
    return d;
}
