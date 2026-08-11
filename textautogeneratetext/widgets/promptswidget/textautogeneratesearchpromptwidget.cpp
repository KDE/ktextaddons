/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratesearchpromptwidget.h"
#include <QHBoxLayout>

using namespace TextAutoGenerateText;
TextAutoGenerateSearchPromptWidget::TextAutoGenerateSearchPromptWidget(QWidget *parent)
    : QWidget{parent}
{
}

TextAutoGenerateSearchPromptWidget::~TextAutoGenerateSearchPromptWidget() = default;
#include "moc_textautogeneratesearchpromptwidget.cpp"
