/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "kokoroinstalltexttospeech_export.h"
#include <QObject>
#include <QStringList>
namespace TextEditTextToSpeech
{
class KOKOROINSTALLTEXTTOSPEECH_EXPORT TextToSpeechKokoroCheckJob : public QObject
{
    Q_OBJECT
public:
    struct KOKOROINSTALLTEXTTOSPEECH_EXPORT CheckResult {
        QStringList missing;
        bool needToReinstall = false;

        [[nodiscard]] bool isValid() const;
        [[nodiscard]] QString errorString() const;
    };

    explicit TextToSpeechKokoroCheckJob(QObject *parent = nullptr);
    ~TextToSpeechKokoroCheckJob() override;

    void start();

    [[nodiscard]] bool canStart() const;

    [[nodiscard]] static CheckResult checkSynchronously(int timeoutMs = 30000);

Q_SIGNALS:
    void needToReinstall();
    void packagesInstalled();
    void needToInstallPackages(const QStringList &missing);
};
}
