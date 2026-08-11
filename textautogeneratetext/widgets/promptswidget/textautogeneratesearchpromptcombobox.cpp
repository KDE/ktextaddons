/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchpromptcombobox.h"

using namespace TextAutoGenerateText;
TextAutoGenerateSearchPromptComboBox::TextAutoGenerateSearchPromptComboBox(QWidget *parent)
    : QComboBox(parent)
{
}

TextAutoGenerateSearchPromptComboBox::~TextAutoGenerateSearchPromptComboBox() = default;

#include "moc_textautogeneratesearchpromptcombobox.cpp"
