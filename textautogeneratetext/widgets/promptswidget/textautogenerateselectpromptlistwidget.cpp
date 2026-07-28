/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateselectpromptlistwidget.h"

using namespace TextAutoGenerateText;
TextAutoGenerateSelectPromptListWidget::TextAutoGenerateSelectPromptListWidget(QWidget *parent)
    : QListWidget(parent)
{
}

TextAutoGenerateSelectPromptListWidget::~TextAutoGenerateSelectPromptListWidget() = default;
#include "moc_textautogenerateselectpromptlistwidget.cpp"
