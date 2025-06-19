/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextmodelcombobox.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextModelComboBox::TextAutoGenerateTextModelComboBox(QWidget *parent)
    : QComboBox(parent)
{
}

TextAutoGenerateTextModelComboBox::~TextAutoGenerateTextModelComboBox() = default;

#include "moc_textautogeneratetextmodelcombobox.cpp"
