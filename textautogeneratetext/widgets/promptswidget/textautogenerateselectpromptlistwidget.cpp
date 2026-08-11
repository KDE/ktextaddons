/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateselectpromptlistwidget.h"
#include "textautogenerateselectpromptdelegate.h"
using namespace TextAutoGenerateText;
TextAutoGenerateSelectPromptListWidget::TextAutoGenerateSelectPromptListWidget(QWidget *parent)
    : QListView(parent)
{
    setItemDelegate(new TextAutoGenerateSelectPromptDelegate(this));
}

TextAutoGenerateSelectPromptListWidget::~TextAutoGenerateSelectPromptListWidget() = default;
#include "moc_textautogenerateselectpromptlistwidget.cpp"
