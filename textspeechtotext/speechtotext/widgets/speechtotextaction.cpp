/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextaction.h"
#include "textspeechtotext/speechtotextmanager.h"
using namespace TextSpeechToText;
SpeechToTextAction::SpeechToTextAction(QObject *parent)
    : QAction{parent}
{
    connect(this, &QAction::trigger, this, &SpeechToTextAction::slotClicked);
}

SpeechToTextAction::~SpeechToTextAction() = default;

void SpeechToTextAction::slotClicked()
{
    // TODO
}

#include "moc_speechtotextaction.cpp"
