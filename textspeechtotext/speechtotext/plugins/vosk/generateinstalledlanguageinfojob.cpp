/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "generateinstalledlanguageinfojob.h"
#include "libvoskspeechtotext_debug.h"
#include <KLocalizedString>

GenerateInstalledLanguageInfoJob::GenerateInstalledLanguageInfoJob(QObject *parent)
    : QObject{parent}
{
}

GenerateInstalledLanguageInfoJob::~GenerateInstalledLanguageInfoJob() = default;

void GenerateInstalledLanguageInfoJob::start()
{
    if (canStart()) {
        if (!VoskEngineUtils::createInstalledLanguageInfo(mInfo.pathToStore, mInfo.info)) {
            qCWarning(LIBVOSKSPEECHTOTEXT_LOG) << " Impossible to store installed language info";
            Q_EMIT errorText(i18n("Impossible to store language info."));
        }
    }
    Q_EMIT generatedDone();
    deleteLater();
}

bool GenerateInstalledLanguageInfoJob::canStart() const
{
    return mInfo.isValid();
}

GenerateInstalledLanguageInfoJob::LanguageInfo GenerateInstalledLanguageInfoJob::info() const
{
    return mInfo;
}

void GenerateInstalledLanguageInfoJob::setInfo(const GenerateInstalledLanguageInfoJob::LanguageInfo &newInfo)
{
    mInfo = newInfo;
}

bool GenerateInstalledLanguageInfoJob::LanguageInfo::isValid() const
{
    return !pathToStore.isEmpty() && info.isValid();
}

#include "moc_generateinstalledlanguageinfojob.cpp"
