/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "downloadlanguagejob.h"

DownloadLanguageJob::DownloadLanguageJob(QObject *parent)
    : QObject{parent}
{
}

DownloadLanguageJob::~DownloadLanguageJob() = default;

void DownloadLanguageJob::start()
{
    // TODO
}

bool DownloadLanguageJob::canStart() const
{
    // TODO
    return false;
}
