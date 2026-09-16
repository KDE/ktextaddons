/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "speechtotextwhisperinstall_export.h"
#include <QStringList>
#include <QWidget>
class QPlainTextEdit;
class QProgressBar;
class QPushButton;
class WhisperSpeechToTextModelComboBox;

/*!
 * \brief Installs the python side of whisper, and the model it transcribes with.
 *
 * The modules to install are the ones WhisperSpeechToTextCheckJob reported as
 * missing; the widget creates the virtualenv with
 * WhisperSpeechToTextInstallPythonEvenvJob, then drives
 * WhisperSpeechToTextInstallJob and shows what pip prints.
 *
 * The model is the other half of the installation: choosing it here and
 * downloading it with WhisperSpeechToTextDownloadModelJob is what spares the
 * user a first dictation which seems to hang while several hundred megabytes
 * are fetched.
 */
class SPEECHTOTEXTWHISPERINSTALL_EXPORT WhisperSpeechToTextInstallPythonWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WhisperSpeechToTextInstallPythonWidget(QWidget *parent = nullptr);
    ~WhisperSpeechToTextInstallPythonWidget() override;

    [[nodiscard]] QStringList modules() const;
    void setModules(const QStringList &newModules);

    void startInstall();

Q_SIGNALS:
    void installDone();
    void installFailed();
    void installInProgress(bool status);

private:
    SPEECHTOTEXTWHISPERINSTALL_NO_EXPORT void appendMessage(const QString &message);
    SPEECHTOTEXTWHISPERINSTALL_NO_EXPORT void installModules();
    SPEECHTOTEXTWHISPERINSTALL_NO_EXPORT void downloadModel();
    SPEECHTOTEXTWHISPERINSTALL_NO_EXPORT void warnWhenModelIsNotDownloaded();
    SPEECHTOTEXTWHISPERINSTALL_NO_EXPORT void setDownloadInProgress(bool inProgress);

    QPlainTextEdit *const mPlainTextEdit;
    WhisperSpeechToTextModelComboBox *const mModelComboBox;
    QPushButton *const mDownloadModelButton;
    QProgressBar *const mDownloadProgressBar;
    QStringList mModules;
};
