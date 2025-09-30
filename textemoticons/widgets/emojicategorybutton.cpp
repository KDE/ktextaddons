/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emojicategorybutton.h"
using namespace TextEmoticonsWidgets;
EmojiCategoryButton::EmojiCategoryButton(QWidget *parent)
    : QToolButton(parent)
{
    setCheckable(true);
    setAutoRaise(true);
}

EmojiCategoryButton::~EmojiCategoryButton() = default;

#include "moc_emojicategorybutton.cpp"
