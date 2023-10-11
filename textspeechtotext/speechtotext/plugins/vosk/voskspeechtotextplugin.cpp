/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskspeechtotextplugin.h"

VoskSpeechToTextPlugin::VoskSpeechToTextPlugin(QObject *parent)
    : TextSpeechToText::SpeechToTextPlugin{parent}
{
}

VoskSpeechToTextPlugin::~VoskSpeechToTextPlugin() = default;

void VoskSpeechToTextPlugin::speechToText()
{
    // TODO
}

int VoskSpeechToTextPlugin::sampleRate() const
{
    return 16000;
}

QString VoskSpeechToTextPlugin::defaultLanguage() const
{
    // TODO
    return {};
}

#include "moc_voskspeechtotextplugin.cpp"
