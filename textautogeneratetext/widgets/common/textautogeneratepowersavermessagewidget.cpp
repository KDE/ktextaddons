/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratepowersavermessagewidget.h"

using namespace TextAutoGenerateText;
TextAutoGeneratePowerSaverMessageWidget::TextAutoGeneratePowerSaverMessageWidget(QWidget *parent)
    : KMessageWidget(parent)
{
}

TextAutoGeneratePowerSaverMessageWidget::~TextAutoGeneratePowerSaverMessageWidget() = default;
#include "moc_textautogeneratepowersavermessagewidget.cpp"
