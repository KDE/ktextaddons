/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "whisperspeechtotextclient.h"
#include "whisperspeechtotextplugin.h"
#include <KLocalizedString>

WhisperSpeechToTextClient::WhisperSpeechToTextClient(QObject *parent)
    : TextSpeechToText::SpeechToTextClient{parent}
{
}

WhisperSpeechToTextClient::~WhisperSpeechToTextClient() = default;

QString WhisperSpeechToTextClient::name() const
{
    return QStringLiteral("whisper");
}

QString WhisperSpeechToTextClient::translatedName() const
{
    return i18n("Whisper");
}

TextSpeechToText::SpeechToTextClient::EngineType WhisperSpeechToTextClient::engineType() const
{
    return TextSpeechToText::SpeechToTextClient::Locale;
}

TextSpeechToText::SpeechToTextPlugin *WhisperSpeechToTextClient::createTextToSpeech()
{
    // TODO
    return new WhisperSpeechToTextPlugin;
}

#include "moc_whisperspeechtotextclient.cpp"
