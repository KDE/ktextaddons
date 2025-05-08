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
