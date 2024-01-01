/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "googlespeechtotextpluginjob.h"

GoogleSpeechToTextPluginJob::GoogleSpeechToTextPluginJob(QObject *parent)
    : QObject{parent}
{
}

GoogleSpeechToTextPluginJob::~GoogleSpeechToTextPluginJob() = default;

#include "moc_googlespeechtotextpluginjob.cpp"
