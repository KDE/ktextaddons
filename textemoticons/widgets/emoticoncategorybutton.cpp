/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emoticoncategorybutton.h"
using namespace TextEmoticonsWidgets;
EmoticonCategoryButton::EmoticonCategoryButton(QWidget *parent)
    : QToolButton(parent)
{
    setCheckable(true);
    setAutoRaise(true);
}

EmoticonCategoryButton::~EmoticonCategoryButton() = default;

#include "moc_emoticoncategorybutton.cpp"
