/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotexttoolbuttonwidget.h"
using namespace TextSpeechToText;
SpeechToTextToolButtonWidget::SpeechToTextToolButtonWidget(QWidget *parent)
    : QWidget{parent}
{
}

SpeechToTextToolButtonWidget::~SpeechToTextToolButtonWidget() = default;

#include "moc_speechtotexttoolbuttonwidget.cpp"
