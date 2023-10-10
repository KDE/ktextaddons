/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "downloadlanguagejob.h"
#include "libvoskspeechtotext_private_export.h"

#include <QObject>

class LIBVOSKSPEECHTOTEXT_TESTS_EXPORT GenerateInstalledLanguageInfoJob : public QObject
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
