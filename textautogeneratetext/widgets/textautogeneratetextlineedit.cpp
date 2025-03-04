/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextlineedit.h"
#include <KLineEditEventHandler>

using namespace TextAutogenerateText;
TextAutogenerateTextLineEdit::TextAutogenerateTextLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    KLineEditEventHandler::catchReturnKey(this);
}

TextAutogenerateTextLineEdit::~TextAutogenerateTextLineEdit() = default;

#include "moc_textautogeneratetextlineedit.cpp"
