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
    setCheckable(true);
    connect(this, &QAction::triggered, this, &SpeechToTextAction::slotClicked);

    connect(SpeechToTextManager::self(), &SpeechToTextManager::recordingChanged, this, [this](bool recording) {
        setChecked(recording);
        updateIcon();
    });
    updateIcon();
}

SpeechToTextAction::~SpeechToTextAction() = default;

void SpeechToTextAction::updateIcon()
{
    setIcon(isChecked() ? QIcon::fromTheme(u"mic-on"_s) : QIcon::fromTheme(u"mic-off"_s));
}

void SpeechToTextAction::slotClicked()
{
    if (SpeechToTextManager::self()->isRecording()) {
        SpeechToTextManager::self()->stop();
    } else {
        SpeechToTextManager::self()->speechToText();
    }
    // Starting can fail (no engine, no microphone): keep the action in sync with reality.
    setChecked(SpeechToTextManager::self()->isRecording());
}

#include "moc_speechtotextaction.cpp"
