/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextplugin.h"

WhisperSpeechToTextPlugin::WhisperSpeechToTextPlugin(QObject *parent)
    : TextSpeechToText::SpeechToTextPlugin{parent}
{
}

WhisperSpeechToTextPlugin::~WhisperSpeechToTextPlugin() = default;

void WhisperSpeechToTextPlugin::speechToText()
{
    // TODO
}

int WhisperSpeechToTextPlugin::sampleRate() const
{
    return 16000;
}

QIODevice *WhisperSpeechToTextPlugin::audioDevice() const
{
    return nullptr;
}

bool WhisperSpeechToTextPlugin::loadSettings()
{
    return false;
    // TODO
}

void WhisperSpeechToTextPlugin::clear()
{
    // TODO
}

#include "moc_whisperspeechtotextplugin.cpp"
