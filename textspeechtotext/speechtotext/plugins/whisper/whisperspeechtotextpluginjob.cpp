/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextpluginjob.h"

WhisperSpeechToTextPluginJob::WhisperSpeechToTextPluginJob(QObject *parent)
    : QObject{parent}
{
}

WhisperSpeechToTextPluginJob::~WhisperSpeechToTextPluginJob() = default;

void WhisperSpeechToTextPluginJob::start()
{
    // TODO
}

#include "moc_whisperspeechtotextpluginjob.cpp"
