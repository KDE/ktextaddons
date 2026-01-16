/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextaction.h"

#include "textspeechtotext/speechtotextmanager.h"
using namespace TextSpeechToText;
using namespace Qt::Literals::StringLiterals;
SpeechToTextAction::SpeechToTextAction(QObject *parent)
    : QAction{parent}
{
    connect(this, &QAction::triggered, this, &SpeechToTextAction::slotClicked);
}

SpeechToTextAction::~SpeechToTextAction() = default;

void SpeechToTextAction::slotClicked()
{
    SpeechToTextManager::self()->speechToText();
}

#include "moc_speechtotextaction.cpp"
