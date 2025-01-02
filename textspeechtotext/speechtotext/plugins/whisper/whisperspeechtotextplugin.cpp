/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextplugin.h"
#include <QDebug>

WhisperSpeechToTextPlugin::WhisperSpeechToTextPlugin(QObject *parent)
    : TextSpeechToText::SpeechToTextPlugin{parent}
{
}

WhisperSpeechToTextPlugin::~WhisperSpeechToTextPlugin() = default;

void WhisperSpeechToTextPlugin::speechToText()
{
    qWarning() << "Not implemented yet";
    // TODO
}

int WhisperSpeechToTextPlugin::sampleRate() const
{
    return 16000;
}

QIODevice *WhisperSpeechToTextPlugin::audioDevice() const
{
    qWarning() << "Not implemented yet";
    return nullptr;
}

bool WhisperSpeechToTextPlugin::loadSettings()
{
    qWarning() << "Not implemented yet";
    return false;
    // TODO
}

void WhisperSpeechToTextPlugin::clear()
{
    qWarning() << "Not implemented yet";
    // TODO
}

#include "moc_whisperspeechtotextplugin.cpp"
