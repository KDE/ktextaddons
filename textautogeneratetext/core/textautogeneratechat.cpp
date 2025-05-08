/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratechat.h"

using namespace TextAutogenerateText;
TextAutoGenerateChat::TextAutoGenerateChat() = default;

TextAutoGenerateChat::~TextAutoGenerateChat() = default;

bool TextAutoGenerateChat::favorite() const
{
    return mFavorite;
}

void TextAutoGenerateChat::setFavorite(bool newFavorite)
{
    mFavorite = newFavorite;
}

bool TextAutoGenerateChat::archived() const
{
    return mArchived;
}

void TextAutoGenerateChat::setArchived(bool newArchived)
{
    mArchived = newArchived;
}

QByteArray TextAutoGenerateChat::identifier() const
{
    return mIdentifier;
}

void TextAutoGenerateChat::setIdentifier(const QByteArray &newIdentifier)
{
    mIdentifier = newIdentifier;
}

QDebug operator<<(QDebug d, const TextAutogenerateText::TextAutoGenerateChat &t)
{
    d.space() << "favorite:" << t.favorite();
    d.space() << "archived:" << t.archived();
    d.space() << "identifier:" << t.identifier();
    return d;
}

#include "moc_textautogeneratechat.cpp"
