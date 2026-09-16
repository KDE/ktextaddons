/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class WhisperSpeechToTextInstallPythonWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit WhisperSpeechToTextInstallPythonWidgetTest(QObject *parent = nullptr);
    ~WhisperSpeechToTextInstallPythonWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldAssignModules();
    void shouldNotInstallWithoutModules();
};
