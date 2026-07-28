/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateselectpromptwidget.h"
#include <QVBoxLayout>
using namespace TextAutoGenerateText;
TextAutoGenerateSelectPromptWidget::TextAutoGenerateSelectPromptWidget(QWidget *parent)
    : QWidget{parent}
{
}

TextAutoGenerateSelectPromptWidget::~TextAutoGenerateSelectPromptWidget() = default;
#include "moc_textautogenerateselectpromptwidget.cpp"
