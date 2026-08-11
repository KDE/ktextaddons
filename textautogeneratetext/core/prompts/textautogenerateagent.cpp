/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateagent.h"
#include <QDebug>

using namespace TextAutoGenerateText;
TextAutoGenerateAgent::TextAutoGenerateAgent()
    : mIdentifier(QUuid::createUuid().toByteArray(QUuid::Id128))
{
}

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

QByteArray TextAutoGenerateAgent::identifier() const
{
    return mIdentifier;
}

void TextAutoGenerateAgent::setIdentifier(const QByteArray &newIdentifier)
{
    mIdentifier = newIdentifier;
}

bool TextAutoGenerateAgent::isValid() const
{
    return !mIdentifier.isEmpty() && !mName.isEmpty();
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateAgent &t)
{
    d.space() << "name:" << t.name();
    d.space() << "description:" << t.description();
    d.space() << "identifier:" << t.identifier();
    return d;
}
