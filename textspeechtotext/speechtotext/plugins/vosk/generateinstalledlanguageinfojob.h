/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "libvoskspeechtotext_private_export.h"

#include "voskengineutils.h"
#include <QObject>

class LIBVOSKSPEECHTOTEXT_TESTS_EXPORT GenerateInstalledLanguageInfoJob : public QObject
{
    Q_OBJECT
public:
    struct LIBVOSKSPEECHTOTEXT_TESTS_EXPORT LanguageInfo {
        VoskEngineUtils::LanguageInstalled info;
        QString pathToStore;
        [[nodiscard]] bool isValid() const;
    };
    explicit GenerateInstalledLanguageInfoJob(QObject *parent = nullptr);
    ~GenerateInstalledLanguageInfoJob() override;

    void start();
    [[nodiscard]] bool canStart() const;

    [[nodiscard]] GenerateInstalledLanguageInfoJob::LanguageInfo info() const;
    void setInfo(const GenerateInstalledLanguageInfoJob::LanguageInfo &newInfo);

Q_SIGNALS:
    void generatedDone();
    void errorText(const QString &str);

private:
    GenerateInstalledLanguageInfoJob::LanguageInfo mInfo;
};
LIBVOSKSPEECHTOTEXT_EXPORT QDebug operator<<(QDebug d, const GenerateInstalledLanguageInfoJob::LanguageInfo &t);
