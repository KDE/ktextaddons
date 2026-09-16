/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "speechtotextwhisperinstall_export.h"
#include <QProcess>
#include <QStringList>

/*!
 * \brief Installs the python modules whisper_helper.py needs.
 *
 * The virtualenv is created first when it is missing, then the modules are
 * installed in it one after the other with its own pip: on a distribution
 * which follows PEP 668 pip refuses to touch the system python anyway.
 * The job deletes itself once it has reported the outcome.
 */
class SPEECHTOTEXTWHISPERINSTALL_EXPORT WhisperSpeechToTextInstallJob : public QObject
{
    Q_OBJECT
public:
    explicit WhisperSpeechToTextInstallJob(QObject *parent = nullptr);
    ~WhisperSpeechToTextInstallJob() override;

    [[nodiscard]] bool canStart() const;
    void start();

    [[nodiscard]] QStringList modules() const;
    void setModules(const QStringList &newModules);

Q_SIGNALS:
    void installDone();
    void installFailed();
    /*! Output of pip, so that the progress can be shown to the user. */
    void installMessage(const QString &message);

private:
    void createVenv();
    void installNextModule();
    void slotFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void failed(const QString &errorMessage);

    QStringList mModules;
    QStringList mRemainingModules;
    QProcess *mProcess = nullptr;
    bool mCreatingVenv = false;
};
