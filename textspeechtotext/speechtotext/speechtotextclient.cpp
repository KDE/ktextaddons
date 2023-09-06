/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextclient.h"
using namespace TextSpeechToText;
SpeechToTextClient::SpeechToTextClient(QObject *parent)
    : QObject{parent}
{
}

SpeechToTextClient::~SpeechToTextClient() = default;

bool SpeechToTextClient::hasConfigurationDialog() const
{
    return false;
}

#include "moc_speechtotextclient.cpp"
