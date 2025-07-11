/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "googlespeechtotextclient.h"
using namespace Qt::Literals::StringLiterals;

#include "googlespeechtotextplugin.h"
#include <KLocalizedString>

GoogleSpeechToTextClient::GoogleSpeechToTextClient(QObject *parent)
    : TextSpeechToText::SpeechToTextClient{parent}
{
}

GoogleSpeechToTextClient::~GoogleSpeechToTextClient() = default;

QString GoogleSpeechToTextClient::name() const
{
    return u"google"_s;
}

QString GoogleSpeechToTextClient::translatedName() const
{
    return i18n("Google");
}

TextSpeechToText::SpeechToTextClient::EngineType GoogleSpeechToTextClient::engineType() const
{
    return TextSpeechToText::SpeechToTextClient::Network;
}

TextSpeechToText::SpeechToTextPlugin *GoogleSpeechToTextClient::createTextToSpeech()
{
    return new GoogleSpeechToTextPlugin;
}

#include "moc_googlespeechtotextclient.cpp"
