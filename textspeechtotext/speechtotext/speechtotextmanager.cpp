/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "speechtotextmanager.h"
#include "speechtotextengineloader.h"
using namespace TextSpeechToText;
SpeechToTextManager::SpeechToTextManager(QObject *parent)
    : QObject{parent}
{
}

SpeechToTextManager::~SpeechToTextManager() = default;

void SpeechToTextManager::switchEngine(const QString &engineName)
{
    // TODO
}

#include "moc_speechtotextmanager.cpp"
