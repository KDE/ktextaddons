/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

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

QString WhisperSpeechToTextPlugin::defaultLanguage() const
{
    // TODO
    return {};
}

#include "moc_whisperspeechtotextplugin.cpp"
