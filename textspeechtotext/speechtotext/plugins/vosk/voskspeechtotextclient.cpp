/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "voskspeechtotextclient.h"
#include <KLocalizedString>

VoskSpeechToTextClient::VoskSpeechToTextClient(QObject *parent)
    : TextSpeechToText::SpeechToTextClient{parent}
{
}

VoskSpeechToTextClient::~VoskSpeechToTextClient() = default;

QString VoskSpeechToTextClient::name() const
{
    return QStringLiteral("google");
}

QString VoskSpeechToTextClient::translatedName() const
{
    return i18n("Google");
}

TextSpeechToText::SpeechToTextClient::EngineType VoskSpeechToTextClient::engineType() const
{
    return TextSpeechToText::SpeechToTextClient::Network;
}

TextSpeechToText::SpeechToTextPlugin *VoskSpeechToTextClient::createTextToSpeech()
{
    // TODO
    return {};
}

#include "moc_voskspeechtotextclient.cpp"
