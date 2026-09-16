/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "speechtotextwhisperinstall_export.h"
#include <QStringList>
#include <QWidget>
class QPlainTextEdit;

/*!
 * \brief Shows the progress of the installation of the python modules whisper needs.
 *
 * The modules to install are the ones WhisperSpeechToTextCheckJob reported as
 * missing; the widget only drives WhisperSpeechToTextInstallJob and shows what
 * pip prints.
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

    QPlainTextEdit *const mPlainTextEdit;
    QStringList mModules;
};
