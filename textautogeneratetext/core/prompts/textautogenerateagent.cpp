/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateagent.h"

using namespace TextAutoGenerateText;
TextAutoGenerateAgent::TextAutoGenerateAgent() = default;
TextAutoGenerateAgent::~TextAutoGenerateAgent() = default;

QString TextAutoGenerateAgent::name() const
{
    return mName;
}

void TextAutoGenerateAgent::setName(const QString &newName)
{
    mName = newName;
}

QString TextAutoGenerateAgent::description() const
{
    return mDescription;
}

void TextAutoGenerateAgent::setDescription(const QString &newDescription)
{
    mDescription = newDescription;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateAgent &t)
{
    d.space() << "name:" << t.name();
    d.space() << "description:" << t.description();
    return d;
}
