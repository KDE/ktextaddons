/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "downloadlanguagejob.h"

#include <QObject>

class GenerateInstalledLanguageInfoJob : public QObject
{
    Q_OBJECT
public:
    explicit GenerateInstalledLanguageInfoJob(QObject *parent = nullptr);
    ~GenerateInstalledLanguageInfoJob() override;

    void start();
    Q_REQUIRED_RESULT bool canStart() const;

    DownloadLanguageJob::DownloadLanguageInfo info() const;
    void setInfo(const DownloadLanguageJob::DownloadLanguageInfo &newInfo);

Q_SIGNALS:
    void generatedDone();
    void errorText(const QString &str);

private:
    DownloadLanguageJob::DownloadLanguageInfo mInfo;
};
