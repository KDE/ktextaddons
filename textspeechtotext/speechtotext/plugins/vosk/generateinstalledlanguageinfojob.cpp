/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "generateinstalledlanguageinfojob.h"

GenerateInstalledLanguageInfoJob::GenerateInstalledLanguageInfoJob(QObject *parent)
    : QObject{parent}
{
}

GenerateInstalledLanguageInfoJob::~GenerateInstalledLanguageInfoJob() = default;

void GenerateInstalledLanguageInfoJob::start()
{
    // TODO
    // Generate json file.
    deleteLater();
}

bool GenerateInstalledLanguageInfoJob::canStart() const
{
    return mInfo.isValid();
}

DownloadLanguageJob::DownloadLanguageInfo GenerateInstalledLanguageInfoJob::info() const
{
    return mInfo;
}

void GenerateInstalledLanguageInfoJob::setInfo(const DownloadLanguageJob::DownloadLanguageInfo &newInfo)
{
    mInfo = newInfo;
}

#include "moc_generateinstalledlanguageinfojob.cpp"
