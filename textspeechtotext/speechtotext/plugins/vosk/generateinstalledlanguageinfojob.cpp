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
}

bool GenerateInstalledLanguageInfoJob::canStart() const
{
    // TODO
    return {};
}

#include "moc_generateinstalledlanguageinfojob.cpp"
