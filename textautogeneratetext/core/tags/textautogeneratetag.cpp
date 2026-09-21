/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetag.h"
#include <QDebug>

using namespace TextAutoGenerateText;
TextAutoGenerateTag::TextAutoGenerateTag() = default;

QString TextAutoGenerateTag::name() const
{
    return mName;
}

void TextAutoGenerateTag::setName(const QString &newName)
{
    mName = newName;
}

QByteArray TextAutoGenerateTag::identifier() const
{
    return mIdentifier;
}

void TextAutoGenerateTag::setIdentifier(const QByteArray &newIdentifier)
{
    mIdentifier = newIdentifier;
}

QColor TextAutoGenerateTag::color() const
{
    return mColor;
}

void TextAutoGenerateTag::setColor(const QColor &newColor)
{
    mColor = newColor;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTag &t)
{
    d.space() << "mName" << t.name();
    d.space() << "mIdentifier" << t.identifier();
    return d;
}
