/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextclient.h"
using namespace Qt::Literals::StringLiterals;

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

bool SpeechToTextClient::showConfigureDialog([[maybe_unused]] QWidget *parentWidget)
{
    // Nothing by default
    return false;
}

#include "moc_speechtotextclient.cpp"
