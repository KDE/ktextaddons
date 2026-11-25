/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "libretranslatelanguagejob.h"
#include "libretranslatetranslator_debug.h"
#include <TextTranslator/TranslatorEngineAccessManager>

LibreTranslateLanguageJob::LibreTranslateLanguageJob(QObject *parent)
    : QObject{parent}
{
}

LibreTranslateLanguageJob::~LibreTranslateLanguageJob() = default;

bool LibreTranslateLanguageJob::canStart() const
{
    return mInfo.isValid();
}

void LibreTranslateLanguageJob::start()
{
    if (!canStart()) {
        qCWarning(TRANSLATOR_LIBRETRANSLATE_LOG) << "Impossible to start LibreTranslateLanguageJob";
        Q_EMIT getLanguagesFailed();
        deleteLater();
        return;
    }
    // TODO
    deleteLater();
}

LibreTranslateLanguageJob::LibreTranslateLanguageInfo LibreTranslateLanguageJob::info() const
{
    return mInfo;
}

void LibreTranslateLanguageJob::setInfo(const LibreTranslateLanguageInfo &newInfo)
{
    mInfo = newInfo;
}

bool LibreTranslateLanguageJob::LibreTranslateLanguageInfo::isValid() const
{
    return !apiKey.isEmpty() || !serverUrl.isEmpty();
}
#include "moc_libretranslatelanguagejob.cpp"
