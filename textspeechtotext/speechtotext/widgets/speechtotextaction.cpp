/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextaction.h"
using namespace TextSpeechToText;
SpeechToTextAction::SpeechToTextAction(QObject *parent)
    : QAction{parent}
{
}

SpeechToTextAction::~SpeechToTextAction() = default;

#include "moc_speechtotextaction.cpp"
