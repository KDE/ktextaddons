/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>
namespace TextEditTextToSpeech
{
class TextToSpeechKokoroCheckJob : public QObject
{
    Q_OBJECT
public:
    explicit TextToSpeechKokoroCheckJob(QObject *parent = nullptr);
    ~TextToSpeechKokoroCheckJob() override;

    void start();

    [[nodiscard]] bool canStart() const;

Q_SIGNALS:
    void needToReinstall();
    void packagesInstalled();
    void needToInstallPackages(const QStringList &missing);
};
}
