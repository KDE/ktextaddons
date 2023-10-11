/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

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

QString GoogleSpeechToTextPlugin::defaultLanguage() const
{
    // TODO
    return {};
}

#include "moc_googlespeechtotextplugin.cpp"
