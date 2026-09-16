/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "speechtotextwhisperinstall_export.h"
#include <QDialog>
#include <QStringList>
class QPushButton;
class WhisperSpeechToTextInstallPythonWidget;

/*!
 * \brief Wraps WhisperSpeechToTextInstallPythonWidget in a dialog.
 *
 * The close button stays disabled while pip is running: closing the dialog
 * would kill it in the middle of the installation.
 */
class SPEECHTOTEXTWHISPERINSTALL_EXPORT WhisperSpeechToTextInstallPythonDialog : public QDialog
{
    Q_OBJECT
public:
    explicit WhisperSpeechToTextInstallPythonDialog(QWidget *parent = nullptr);
    ~WhisperSpeechToTextInstallPythonDialog() override;

    void setModules(const QStringList &modules);
    void startInstall();

private:
    WhisperSpeechToTextInstallPythonWidget *const mWhisperInstallPythonWidget;
    QPushButton *const mCloseButton;
};
