/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "speechtotextwhisperinstall_export.h"
#include <QObject>

/*!
 * \brief Creates the python virtual environment used by whisper.
 *
 * The existing environment is removed first, so that a broken or outdated
 * installation is replaced by a pristine one.
 * The job deletes itself once it has reported the outcome.
 */
class SPEECHTOTEXTWHISPERINSTALL_EXPORT WhisperSpeechToTextInstallPythonEvenvJob : public QObject
{
    Q_OBJECT
public:
    explicit WhisperSpeechToTextInstallPythonEvenvJob(QObject *parent = nullptr);
    ~WhisperSpeechToTextInstallPythonEvenvJob() override;

    [[nodiscard]] bool canStart() const;

    void start();

Q_SIGNALS:
    void installFailed();
    void installDone();
};
