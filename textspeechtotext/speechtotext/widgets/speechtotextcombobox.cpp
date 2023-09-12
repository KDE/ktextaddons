/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextcombobox.h"
using namespace TextSpeechToText;
SpeechToTextComboBox::SpeechToTextComboBox(QWidget *parent)
    : QComboBox(parent)
{
}

SpeechToTextComboBox::~SpeechToTextComboBox() = default;

#include "moc_speechtotextcombobox.cpp"
