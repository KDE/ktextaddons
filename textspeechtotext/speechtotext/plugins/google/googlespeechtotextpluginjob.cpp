/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "googlespeechtotextpluginjob.h"

GoogleSpeechToTextPluginJob::GoogleSpeechToTextPluginJob(QObject *parent)
    : QObject{parent}
{
}

GoogleSpeechToTextPluginJob::~GoogleSpeechToTextPluginJob() = default;

void GoogleSpeechToTextPluginJob::start()
{
    // TODO
}

#include "moc_googlespeechtotextpluginjob.cpp"
