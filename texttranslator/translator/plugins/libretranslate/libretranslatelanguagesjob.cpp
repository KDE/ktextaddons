/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "libretranslatelanguagesjob.h"
#include "libretranslatetranslator_debug.h"
#include <TextTranslator/TranslatorEngineAccessManager>

LibreTranslateLanguagesJob::LibreTranslateLanguagesJob(QObject *parent)
    : QObject{parent}
{
}

LibreTranslateLanguagesJob::~LibreTranslateLanguagesJob() = default;

bool LibreTranslateLanguagesJob::canStart() const
{
    return mInfo.isValid();
}

void LibreTranslateLanguagesJob::start()
{
    if (!canStart()) {
        qCWarning(TRANSLATOR_LIBRETRANSLATE_LOG) << "Impossible to start LibreTranslateLanguagesJob";
        Q_EMIT getLanguagesFailed();
        deleteLater();
        return;
    }
    // TODO
    deleteLater();
}

LibreTranslateLanguagesJob::LibreTranslateLanguagesInfo LibreTranslateLanguagesJob::info() const
{
    return mInfo;
}

void LibreTranslateLanguagesJob::setInfo(const LibreTranslateLanguagesInfo &newInfo)
{
    mInfo = newInfo;
}

bool LibreTranslateLanguagesJob::LibreTranslateLanguagesInfo::isValid() const
{
    return !serverUrl.isEmpty();
}
#include "moc_libretranslatelanguagesjob.cpp"
