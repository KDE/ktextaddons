/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratesearchlineedit.h"

using namespace TextAutoGenerateText;
TextAutoGenerateSearchLineEdit::TextAutoGenerateSearchLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
}

TextAutoGenerateSearchLineEdit::~TextAutoGenerateSearchLineEdit() = default;

#include "moc_textautogeneratesearchlineedit.cpp"
