/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateskill.h"

using namespace TextAutoGenerateText;
TextAutoGenerateSkill::TextAutoGenerateSkill() = default;
TextAutoGenerateSkill::~TextAutoGenerateSkill() = default;

QString TextAutoGenerateSkill::name() const
{
    return mName;
}

void TextAutoGenerateSkill::setName(const QString &newName)
{
    mName = newName;
}

QString TextAutoGenerateSkill::description() const
{
    return mDescription;
}

void TextAutoGenerateSkill::setDescription(const QString &newDescription)
{
    mDescription = newDescription;
}

QString TextAutoGenerateSkill::instructions() const
{
    return mInstructions;
}

void TextAutoGenerateSkill::setInstructions(const QString &newInstructions)
{
    mInstructions = newInstructions;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateSkill &t)
{
    d.space() << "name:" << t.name();
    d.space() << "description:" << t.description();
    d.space() << "instructions" << t.instructions();
    return d;
}
