/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "speechtotextwhisperinstall_export.h"
#include <QObject>
#include <QStringList>

/*!
 * \brief Asks whisper_helper.py whether faster-whisper is usable.
 *
 * The script is run with its "check" subcommand, which prints on stdout the
 * json describing what is installed. The job deletes itself once it has
 * reported the answer.
 */
class SPEECHTOTEXTWHISPERINSTALL_EXPORT WhisperSpeechToTextCheckJob : public QObject
{
    Q_OBJECT
public:
    struct SPEECHTOTEXTWHISPERINSTALL_EXPORT CheckResult {
        /*! Pip names of the modules which are not installed. */
        QStringList missing;
        /*! Interpreter the script is actually running with. */
        QString pythonExecutable;
        /*! Audio format the script expects, so the engine configures QAudioSource with it. */
        int sampleRate = 0;
        int channels = 0;
        /*! The script did not answer, or answered something which makes no sense. */
        bool needToReinstall = false;

        [[nodiscard]] bool isValid() const;
        [[nodiscard]] QString errorString() const;
    };

    explicit WhisperSpeechToTextCheckJob(QObject *parent = nullptr);
    ~WhisperSpeechToTextCheckJob() override;

    [[nodiscard]] bool canStart() const;
    void start();

    /*! Parses the json printed by "whisper_helper.py check". */
    [[nodiscard]] static CheckResult parseCheckResult(const QByteArray &json);

    /*! Same check, for the callers which cannot wait for a signal. */
    [[nodiscard]] static CheckResult checkSynchronously(int timeoutMs = 30000);

Q_SIGNALS:
    void needToReinstall();
    void packagesInstalled(const WhisperSpeechToTextCheckJob::CheckResult &result);
    void needToInstallPackages(const QStringList &missing);
};

Q_DECLARE_TYPEINFO(WhisperSpeechToTextCheckJob::CheckResult, Q_RELOCATABLE_TYPE);
Q_DECLARE_METATYPE(WhisperSpeechToTextCheckJob::CheckResult)
