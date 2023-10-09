/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "voskspeechtotextclient.h"
#include "voskspeechtotextplugin.h"
#include <KLocalizedString>

VoskSpeechToTextClient::VoskSpeechToTextClient(QObject *parent)
    : TextSpeechToText::SpeechToTextClient{parent}
{
}

VoskSpeechToTextClient::~VoskSpeechToTextClient() = default;

QString VoskSpeechToTextClient::name() const
{
    return QStringLiteral("vosk");
}

QString VoskSpeechToTextClient::translatedName() const
{
    return i18n("Vosk");
}

TextSpeechToText::SpeechToTextClient::EngineType VoskSpeechToTextClient::engineType() const
{
    return TextSpeechToText::SpeechToTextClient::Locale;
}

TextSpeechToText::SpeechToTextPlugin *VoskSpeechToTextClient::createTextToSpeech()
{
    return new VoskSpeechToTextPlugin;
}

bool VoskSpeechToTextClient::hasConfigurationDialog() const
{
    return true;
}

bool VoskSpeechToTextClient::showConfigureDialog(QWidget *parentWidget)
{
    // TODO
    return false;
}

#include "moc_voskspeechtotextclient.cpp"
