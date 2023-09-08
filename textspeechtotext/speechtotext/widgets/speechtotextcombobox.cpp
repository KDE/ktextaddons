/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextcombobox.h"
using namespace TextSpeechToText;
SpeechToTextCombobox::SpeechToTextCombobox(QWidget *parent)
    : QComboBox(parent)
{
}

SpeechToTextCombobox::~SpeechToTextCombobox() = default;

#include "moc_speechtotextcombobox.cpp"
