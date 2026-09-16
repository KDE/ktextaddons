/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class WhisperSpeechToTextInstallPythonDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit WhisperSpeechToTextInstallPythonDialogTest(QObject *parent = nullptr);
    ~WhisperSpeechToTextInstallPythonDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldForwardModulesToWidget();
    void shouldDisableCloseButtonWhileInstalling();
};
