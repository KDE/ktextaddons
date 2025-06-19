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

// TODO add list of model
// TODO get current Model

#include "moc_textautogeneratetextmodelcombobox.cpp"
