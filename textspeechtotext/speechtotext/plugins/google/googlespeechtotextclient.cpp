/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "googlespeechtotextclient.h"

GoogleSpeechToTextClient::GoogleSpeechToTextClient(QObject *parent)
    : TextSpeechToText::SpeechToTextClient{parent}
{
}

GoogleSpeechToTextClient::~GoogleSpeechToTextClient() = default;

#include "moc_googlespeechtotextclient.cpp"
