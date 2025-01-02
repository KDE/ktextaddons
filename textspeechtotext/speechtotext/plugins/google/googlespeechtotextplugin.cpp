/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "googlespeechtotextplugin.h"
#include <QDebug>
GoogleSpeechToTextPlugin::GoogleSpeechToTextPlugin(QObject *parent)
    : TextSpeechToText::SpeechToTextPlugin{parent}
{
}

GoogleSpeechToTextPlugin::~GoogleSpeechToTextPlugin() = default;

void GoogleSpeechToTextPlugin::speechToText()
{
    qWarning() << "Not implemented yet";
    // TODO
}

int GoogleSpeechToTextPlugin::sampleRate() const
{
    return 16000;
}

QIODevice *GoogleSpeechToTextPlugin::audioDevice() const
{
    qWarning() << "Not implemented yet";
    return {};
}

bool GoogleSpeechToTextPlugin::loadSettings()
{
    qWarning() << "Not implemented yet";
    // TODO
    return false;
}

void GoogleSpeechToTextPlugin::clear()
{
    qWarning() << "Not implemented yet";
    // TODO
}

#include "moc_googlespeechtotextplugin.cpp"
