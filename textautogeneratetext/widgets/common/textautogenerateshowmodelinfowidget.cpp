/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateshowmodelinfowidget.h"

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateShowModelInfoWidget::TextAutoGenerateShowModelInfoWidget(QWidget *parent)
    : QWidget{parent}
{
}

TextAutoGenerateShowModelInfoWidget::~TextAutoGenerateShowModelInfoWidget() = default;

#include "moc_textautogenerateshowmodelinfowidget.cpp"
