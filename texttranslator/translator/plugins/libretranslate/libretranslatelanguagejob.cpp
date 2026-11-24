/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "libretranslatelanguagejob.h"

LibreTranslateLanguageJob::LibreTranslateLanguageJob(QObject *parent)
    : QObject{parent}
{
}

LibreTranslateLanguageJob::~LibreTranslateLanguageJob() = default;

bool LibreTranslateLanguageJob::canStart() const
{
    // TODO
    return false;
}

void LibreTranslateLanguageJob::start()
{
    // TODO
    deleteLater();
}
