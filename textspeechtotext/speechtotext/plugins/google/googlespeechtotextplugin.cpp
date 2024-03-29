/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "googlespeechtotextplugin.h"

GoogleSpeechToTextPlugin::GoogleSpeechToTextPlugin(QObject *parent)
    : TextSpeechToText::SpeechToTextPlugin{parent}
{
}

GoogleSpeechToTextPlugin::~GoogleSpeechToTextPlugin() = default;

void GoogleSpeechToTextPlugin::speechToText()
{
    // TODO
}

int GoogleSpeechToTextPlugin::sampleRate() const
{
    return 16000;
}

QIODevice *GoogleSpeechToTextPlugin::audioDevice() const
{
    return {};
}

bool GoogleSpeechToTextPlugin::loadSettings()
{
    // TODO
    return false;
}

void GoogleSpeechToTextPlugin::clear()
{
    // TODO
}

#include "moc_googlespeechtotextplugin.cpp"
