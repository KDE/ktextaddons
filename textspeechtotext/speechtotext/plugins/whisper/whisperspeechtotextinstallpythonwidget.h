/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "speechtotextwhisper_export.h"
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
class SPEECHTOTEXTWHISPER_EXPORT WhisperSpeechToTextInstallPythonWidget : public QWidget
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
    SPEECHTOTEXTWHISPER_NO_EXPORT void appendMessage(const QString &message);

    QPlainTextEdit *const mPlainTextEdit;
    QStringList mModules;
};
